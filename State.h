//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_STATE_H
#define EXGIT_STATE_H

#include <iostream>
#include <utility>
using namespace std;

/**
* class for State
**/
template<typename P>
class State {
  double cost;
  double pathCost;
  bool visited;
  P index;
  State<P> *father;
  string direction;
 public:
  //constructor
  State(P indexF, double costF, State<P> *fatherF, bool visitedF) {
    this->cost = costF;
    this->index = indexF;
    this->father = fatherF;
    this->visited = visitedF;
  }
  //set the cost of the state
  void setCost(int costF) {
    this->cost = costF;
  }
  //get the cost of the state
  double getCost() {
    return cost;
  }
  //set the path cost
  void setPathCost(int pathCostF) {
    this->pathCost = pathCostF;
  }
  //get the path cost
  double getPathCost() {
    return pathCost;
  }
  //get the i of the state
  int getI() {
    return index.first;
  }
  //get the j of the state
  int getJ() {
    return index.second;
  }
  //return the index
  P gatIndex() {
    return index;
  }
  //get the father of the state
  State<P> *getFather() {
    return father;
  }
  //set the father of the state
  void setFather(State<P> *fatherF) {
    this->father = fatherF;
  }
  //set this state has been visited
  void setIsVisited(bool visitedF) {
    this->visited = visitedF;
  }
  //check if this state has been visited
  bool getIsVisited() {
    return this->visited;
  }
  //get the direction
  string getDitrction() {
    return this->direction;
  }
  //set the direction
  void setDirection(string dirF) {
    this->direction = dirF;
  }
  //destructor
  ~State() {}
};

#endif //EXGIT_STATE_H