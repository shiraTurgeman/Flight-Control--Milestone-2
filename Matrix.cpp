//
// Created by shira on 16.1.2020.
//

#include "Matrix.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include "SearcherSolver.h"
#include "BestFirstSearch.h"
#include<bits/stdc++.h>
#include <utility>
#include <algorithm>

#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;
/**
* Class for Matrix
**/
//constructor
Matrix::Matrix(){}
//this method split row by ',' and push to vector
void Matrix::putRowInMatrix(string row){
  string delimiter = ",";
  int k;
  int counter=0;
  for(k=0; k<row.size(); k++){
    if (row[k]==','){
      counter++;
    }
  }
  vector<double> rowVector;
  delimiter = ",";
  string token;
  double num;
  int i=0;
  this->sizeRow = row.length();
  while (i<counter+1) {
    if ((row[i]=='\n')){
      break;
    }else{
      token = row.substr(0, row.find(delimiter));
      num = stof(trim(token));
      rowVector.push_back(num);
      row = trim(row.erase(0, row.find(delimiter)+1));
    }
    i++;
  }
  matrix.push_back(rowVector);
}

//This function deletes unnecessary spaces from words
string Matrix::trim(const string &str){
  size_t first = str.find_first_not_of("\t\n\v\f\r ");
  if (string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of("\t\n\v\f\r ");
  return str.substr(first, (last - first + 1));
}
//return this matrix
vector<vector<double >>  Matrix::getMatrix(){
  return this->matrix;
}
//return this state matrix
vector<vector<State<pair<int, int>>*>>  Matrix::getstateMatrix(){
  return this->stateMatrix;
}

//the the index of the start vertex
pair<int,int> Matrix::getIndexOfStartVertex(){
  int n = matrix.size();
  int j = matrix[n-2].back();
  int i = matrix[n-2].front();
  pair<int,int> indexStart= make_pair(i,j);
 // pair<int, int> p1 = {i, j};                                                         //?????????????????????????????????????
  //*indexStart = p1;
  indexStart.first = i;
  indexStart.second =j;
  return indexStart;
}
//get the index of the end vertex
pair<int,int> Matrix::getIndexOfEndVertex(){
  int n = matrix.size();
  int j = matrix[n-1].back();
  int i = matrix[n-1].front();
  pair<int,int> indexEnd=make_pair(i,j);;
  indexEnd.first = i;
  indexEnd.second =j;
  return indexEnd;
}
//get the I of the end vertex
int Matrix::getIOfEndVertex(){
  int n = matrix.size();
  int j = matrix[n-1].back();
  int i = matrix[n-1].front();
  pair<int,int> indexEndd=make_pair(i,j);
  indexEndd.first = i;
  indexEndd.second =j;
  return indexEndd.first;
}
//get the j of the end vertex
int Matrix::getJOfEndVertex(){
  int n = matrix.size();
  int j = matrix[n-1].back();
  int i = matrix[n-1].front();
  pair<int,int> indexEndj=make_pair(i,j);;
  indexEndj.first = i;
  indexEndj.second =j;
  return indexEndj.second;
}

//get two neighbors vertex
vector<State<pair<int, int>>*> Matrix:: getTwoNeighborsVertex(State<pair<int, int>>* v1, State<pair<int, int>>* v2){
  vector<State<pair<int, int>>*> vectorNeighborsVertex;
  if (v1->getCost()>v2->getCost()){
    vectorNeighborsVertex.push_back(v2);
    vectorNeighborsVertex.push_back(v1);
  }else{
    vectorNeighborsVertex.push_back(v1);
    vectorNeighborsVertex.push_back(v2);
  }
  return vectorNeighborsVertex;
}
//get three neighbors vertex
vector<State<pair<int, int>>*> Matrix:: getThreeNeighborsVertex(State<pair<int, int>>* v1, State<pair<int, int>>* v2,
                                                                State<pair<int, int>>* v3) {
  vector<State<pair<int, int>>*> vectorNeighborsVertex1;
  vector<State<pair<int, int>>*> vectorNeighborsVertex2;
  double costV1 = v1->getCost();
  double costV2 = v2->getCost();
  double costV3 = v3->getCost();
//sort the vector
  vector<pair<double ,State<pair<int,int>>*>> v = { { costV1, v1 }, { costV2, v2 }, { costV3, v3 } };
  sort(v.begin(), v.end());

  int i;
  for(i=0;i<3;i++){
    vectorNeighborsVertex1.push_back(v.back().second);
    v.pop_back();
  }
  for(i=0;i<3;i++){
    vectorNeighborsVertex2.push_back(vectorNeighborsVertex1.back());
    vectorNeighborsVertex1.pop_back();
  }
  return vectorNeighborsVertex2;
}
//get four neighbors vertex
vector<State<pair<int, int>>*> Matrix:: getFourNeighborsVertex(State<pair<int, int>>* v1, State<pair<int, int>>* v2,
                                                               State<pair<int, int>>* v3, State<pair<int, int>>* v4) {

  vector<State<pair<int, int>>*> vectorNeighborsVertex1;

  vector<State<pair<int, int>>*> vectorNeighborsVertex2;
  double costV1 = v1->getCost();
  double costV2 = v2->getCost();
  double costV3 = v3->getCost();
  double costV4 = v4->getCost();
//sort the vector
  vector<pair<double ,State<pair<int,int>>*>> v = { { costV1, v1 }, { costV2, v2 }, { costV3, v3 }, {costV4, v4}};
  sort(v.begin(), v.end());
  int i;
  for(i=0;i<4;i++){
    vectorNeighborsVertex1.push_back(v.back().second);
    v.pop_back();
  }
  for(i=0;i<4;i++){
    vectorNeighborsVertex2.push_back(vectorNeighborsVertex1.back());
    vectorNeighborsVertex1.pop_back();
  }

  return vectorNeighborsVertex2;

}

//create all this neighbors
vector<State<pair<int, int>>*> Matrix::createVectorNeighbors(int i, int j){
  int n = matrix.size()-2-1;                                                //??????????????????
  vector<State<pair<int, int>>*> vectorNeighborsVertex;
  State<pair<int, int>>* v1;
  State<pair<int, int>>* v2;
  State<pair<int, int>>* v3;
  State<pair<int, int>>* v4;
  if (i==0){
    if (j==0){
      v1 = stateMatrix[0][1];
      v2 = stateMatrix[1][0];
      vectorNeighborsVertex = getTwoNeighborsVertex(v1,v2);
    }else if (j==n){
      v1 = stateMatrix[0][n-1];
      v2 = stateMatrix[1][n];
      vectorNeighborsVertex = getTwoNeighborsVertex(v1,v2);
    }else{
      v1 = stateMatrix[0][j-1];
      v2 = stateMatrix[0][j+1];
      v3 = stateMatrix[1][j];
      vectorNeighborsVertex = getThreeNeighborsVertex(v1,v2,v3);
    }
  }else if (i==n){
    if (j==0){
      v1 = stateMatrix[n-1][0];
      v2 = stateMatrix[n][1];
      vectorNeighborsVertex = getTwoNeighborsVertex(v1,v2);
    }else if (j==n){
      v1 = stateMatrix[n-1][n];
      v2 = stateMatrix[n][n-1];
      vectorNeighborsVertex = getTwoNeighborsVertex(v1,v2);
    }else{
      v1 = stateMatrix[n][j-1];
      v2 = stateMatrix[n][j+1];
      v3 = stateMatrix[n-1][j];
      vectorNeighborsVertex = getThreeNeighborsVertex(v1,v2,v3);
    }
  } else if (j==0){
    v1 = stateMatrix[i-1][0];
    v2 = stateMatrix[i+1][0];
    v3 = stateMatrix[i][1];
    vectorNeighborsVertex = getThreeNeighborsVertex(v1,v2,v3);
  } else if (j==n){
    v1 = stateMatrix[i-1][n];
    v2 = stateMatrix[i+1][n];
    v3 = stateMatrix[i][n-1];
    vectorNeighborsVertex = getThreeNeighborsVertex(v1,v2,v3);
  }else{
    v1 = stateMatrix[i-1][j];
    v2 = stateMatrix[i+1][j];
    v3 = stateMatrix[i][j-1];
    v4 = stateMatrix[i][j+1];
    vectorNeighborsVertex = getFourNeighborsVertex(v1,v2,v3,v4);
  }
  return vectorNeighborsVertex;
}
//create the state matrix
void Matrix::createStateMatrix(){
  vector<State<pair<int, int>>*> row;
  State<pair<int, int>>* v;
  int i;
  int j;
  int n = matrix.size()-2;
  for (i=0; i<n; i++) {
    for (j = 0; j < n; j++) {

      v = new State<pair<int, int>>(pair<int, int>(i, j), this->matrix[i][j], nullptr, false);
      v->setIsVisited(false);
      v->setPathCost(0);
      row.push_back(v);
    }
    stateMatrix.push_back(row);
    for (j = 0; j < n; j++) {
      row.pop_back();
    }
  }
}
//get the initial state of the matrix
State<pair<int, int>>* Matrix::getInitialState(){
  int i = getIndexOfStartVertex().first;
  int j = getIndexOfStartVertex().second;
  //cout<< i<<[j]<<" " <<endl;

  return stateMatrix[i][j];
}
//get the goal state
State<pair<int, int>>* Matrix::getGoalState(){
  int i = getIndexOfEndVertex().first;
  int j = getIndexOfEndVertex().second;
  return stateMatrix[i][j];
}
//get the adj of a state
vector<State<pair<int, int>>*> Matrix::getAdj(State<pair<int, int>>* s){
  int i = s->getI();
  int j = s->getJ();
  return createVectorNeighbors(i,j);
}
//check if its is the goal state.
bool Matrix::isGoalState(State<pair<int, int>>* s){
  int iS= s->getI();
  int iJ= s->getJ();
  if ((iS==getIOfEndVertex())&&(iJ==getJOfEndVertex())){
    return true;
  }else{
    return false;
  }
}
//get the direction father.
string Matrix::getDirectionFather(State<pair<int, int>>* vertex){
  State<pair<int, int>>* father;
  father = vertex->getFather();

  int iFather = father->getI();
  int jFather = father->getJ();

  int iCur = vertex->getI();
  int jCur = vertex->getJ();

  if ((iFather==iCur+1)&&(jFather==jCur)){

    return "up";
  }else if ((iFather==iCur-1)&&(jFather==jCur)){
    return "down";
  }else if ((jFather==jCur+1)&&(iFather==iCur)){
    return "left";
  }else if ((jFather==jCur-1)&&(iFather==iCur)){
    return "right";
  }else{
    return "---";
  }


}

//get the path string for the solution
string Matrix::getPathString(State<pair<int, int>>* vertex){
  string path;
  State<pair<int, int>>* start = this->getInitialState();

  list<State<pair<int, int>>*>  returnVector;
  while (vertex->gatIndex() != start->gatIndex()){
    string dir = getDirectionFather(vertex);
    //vertex->setDirection(dir);
    vertex->setDirection(dir);
    returnVector.push_back(vertex);
    vertex=vertex->getFather();
    //lenght++;
    //s=s+current->getCost();
  }
  returnVector.push_back(start);
  returnVector.reverse();
  State<pair<int, int>>* s ;
  for (auto itr = returnVector.begin(); itr!=returnVector.end(); itr++){
    s = *itr;
    if(!(s==start)){
      path = path+s->getDitrction()+" ("+to_string(int(s->getPathCost()))+") ,";
    }
  }

  cout<<endl<<path<<endl;
  return path;

}
//convert this to string
string Matrix::toString() {
  string matrixToString = "";
  string index = "";
  for (int i = 0; i < this->matrix.size(); i++) {
    for (int j = 0; j < this->matrix[i].size() - 1; j++) {
      int num = this->matrix[i][j];
      index = to_string(num);
      matrixToString = matrixToString + index + ",";
    }
  }
  string iStart = to_string(this->getIndexOfStartVertex().first);
  string jStart = to_string(this->getIndexOfStartVertex().second);
  string iEnd = to_string(this->getIndexOfEndVertex().first);
  string jEnd = to_string(this->getIndexOfEndVertex().second);
  matrixToString = matrixToString+iStart+","+jStart+","+iEnd+","+jEnd;

  return matrixToString;
}

ClientHandler* Matrix::duplicate(){
  Searcher<pair<int, int>, State<pair<int, int>> *> *searcher;
  searcher = new BestFirstSearch<pair<int, int>>();
  Solver<Searchable<pair<int, int>> *, State<pair<int, int>> *> *solver;
  solver = new SearcherSolver<pair<int, int>, State<pair<int, int>> *>(searcher);
  auto *newClient = new MyClientHandler<Searchable<pair<int, int>> *, State<pair<int, int>> *>(
      solver, cacheManager);
  return newClient;
}

//destructor
Matrix::~Matrix(){}