
//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_MATRIX_H
#define EXGIT_MATRIX_H

#include <vector>
#include <string>
#include "State.h"
#include "Searchable.h"
#include "ClientHandler.h"
#include "CacheManager.h"
using namespace std;
/**
* Class for Matrix
**/
//template <typename P>
class Matrix: public Searchable<pair<int,int>> {

  vector<vector<double >> matrix;
  vector<vector<State<pair<int, int>>*>>  stateMatrix;
  State<pair<int,int>> *start;
  State<pair<int,int>>  *end;
  int sizeRow;
  CacheManager* cacheManager;


 public:
  virtual ClientHandler* duplicate();

  //constroctor
  Matrix();
  //this method split row by ',' and push to vector
  void putRowInMatrix(string row);
  //This function deletes unnecessary spaces from words
  string trim(const string &str);
  State<pair<int,int>> * getStartVertex();
  State<pair<int,int>> * getEndVertex();
  //the the index of the start vertex
  pair<int,int> getIndexOfStartVertex();
  //get the index of the end vertex
  pair<int,int> getIndexOfEndVertex();
  //get the I of the end vertex
  int getIOfEndVertex();
  //get the J of the end vertex
  int getJOfEndVertex();
  //return this matrix
  vector<vector<double >> getMatrix();
  //this method return matrix with all states for all vertex
  void createStateMatrix();
  //get two neighbors vertex
  vector<State<pair<int, int>>*> getTwoNeighborsVertex(State<pair<int, int>>* v1, State<pair<int, int>>* v2);
  //get three neighbors vertex
  vector<State<pair<int, int>>*> getThreeNeighborsVertex(State<pair<int, int>>* v1, State<pair<int, int>>* v2,
                                                         State<pair<int, int>>* v3);
  //get four neighbors vertex
  vector<State<pair<int, int>>*> getFourNeighborsVertex(State<pair<int, int>>* v1, State<pair<int, int>>* v2,
                                                        State<pair<int, int>>* v3, State<pair<int, int>>* v4);
  //create all this neighbors
  vector<State<pair<int, int>>*> createVectorNeighbors(int i, int j);
  //get the direction father.
  string getDirectionFather(State<pair<int, int>>* vertex);
  //get the path string for the solution
  string getPathString(State<pair<int, int>>* vertex);
  //convert this to string
  string toString();
  vector<State<pair<int, int>>*> getAllStatesForVertex(State<pair<int, int>>* vertex);            //=getAdj. delete this
  State<pair<int, int>>* getInitialState();
  State<pair<int, int>>* getGoalState();
  //convert this to string
  vector<State<pair<int, int>>*> getAdj(State<pair<int, int>>* s);
  //check if its is the goal state.
  bool isGoalState(State<pair<int, int>>*);
  //get state Matrix
  vector<vector<State<pair<int, int>>*>>  getstateMatrix();
  //destroctor
  ~Matrix();
};

#endif //EXGIT_MATRIX_H