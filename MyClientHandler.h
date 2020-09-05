//
// Created by shira on 20.1.2020.
//

#ifndef EX4PROJECT_MYCLIENTHANDLER_H
#define EX4PROJECT_MYCLIENTHANDLER_H

#include "Solver.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "Matrix.h"
#include <mutex>
#include "Searchable.h"
#include "Searcher.h"
#include "AStar.h"
#include "State.h"
using namespace std;

template<typename Problem, typename Solution>
/**
* class for client handler
**/
class MyClientHandler : public ClientHandler{
  //vairable for this class
  Solver<Problem, Solution>* solver;
  CacheManager* cacheManager;
  State<pair<int, int>>* sol= reinterpret_cast<State<pair<int, int>> *>(new pair<int, int>);
  string solution;
  bool boolRead;
  mutex k;


 public:

  //constroctor
  MyClientHandler(Solver<Problem, Solution>* solver, CacheManager* cacheManager){
    this->solver = solver;
    this->cacheManager = cacheManager;
  }

  //handel every client
  void handleClient(int port){
    //create new matrix
    Matrix *matrix = new Matrix();
    char problemLine[1024] = {0};
    int isRead;
    boolRead = true;
    while (boolRead) {
      //read line from the server
      isRead = read(port, problemLine, 1024);
      int j;
      if (isRead < 0) {
        cerr << "error with read" << endl;
      }
      if ((strcmp(problemLine, "end") == 0) || (strcmp(problemLine, "end\n") == 0)
          || (strcmp(problemLine, "end\r\n") == 0)) {
        //end of input
        boolRead = false;
        break;
      } else {
        //insert the numbers to the matrix
        matrix->putRowInMatrix(problemLine);
        for(j=0; j<1023;j++){
          problemLine[j]=0;
        }
        //read line from the server
        isRead = read(port, problemLine, 1023);
        if (isRead == -1) {
          cerr << "error with read" << endl;
        } else if ((strcmp(problemLine, "end") == 0) || (strcmp(problemLine, "end\n") == 0)
            || (strcmp(problemLine, "end\r\n") == 0)) {
          //end of input
          boolRead = false;
          break;
        }else{
          matrix->putRowInMatrix(problemLine);
          for(j=0; j<1023;j++){
            problemLine[j]=0;
          }
        }
      }
    }
    //create the matrix
    matrix->createStateMatrix();
    string problemMat = matrix->toString();
    k.lock();

    if (cacheManager->findSolution(problemMat)){
     // cout<<"11111111"<<endl;
      solution = cacheManager->getSolution(problemMat);
      //cout<<"cost:  "<<solution<<endl;
    } else{
      //cout<<"22222222"<<endl;
      //k.lock();
      sol= solver->solve(matrix);
      //k.unlock();
      //cout<<"33333333   "<<sol->getPathCost()<<"   "<<sol->getCost()<<endl;
      solution = matrix->getPathString(sol);
      cout<<"solution: "<<solution;
      cacheManager->saveSolution(problemMat, solution);
    }
    k.unlock();

    //send to socket
    int is_sent = write(port, solution.c_str(), solution.length());
    //cout << "rrrr" << endl;
    if (is_sent < 0) {
      cout << "problem to send the client" << endl;
    }
  }
  ~MyClientHandler(){}


  string getSol(){
    return this->solution;
  }

  ClientHandler* duplicate(){
    //return clone of this client
    //create new client handler with the same cache manager and clone of solver
    /*Searcher<pair<int, int>, State<pair<int, int>> *> *searcher;
    searcher = new AStar<pair<int, int>>();
    Solver<Searchable<pair<int, int>> *, State<pair<int, int>> *> *solver;
    solver = new SearcherSolver<pair<int, int>, State<pair<int, int>> *>(searcher);*/

    ClientHandler *clientHandler = new MyClientHandler<Searchable<pair<int, int>> *, State<pair<int, int>> *>(this->solver->clone(), this->cacheManager);
  }

};


#endif //EX4PROJECT_MYCLIENTHANDLER_H