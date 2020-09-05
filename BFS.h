//
// Created by noa on 16/01/2020.
//

#ifndef EXGIT__BFS_H_
#define EXGIT__BFS_H_

#include "Searcher.h"
#include <unordered_set>
#include <queue>
#include <stack>
#include <list>
#include "AbstractSearcher.h"
using namespace std;

/**
* class for BFS
**/
template<class T>

class BFS : public AbstractSearcher<T>  {
 private:
  //variable for the algorithm
  int numOfVisitVertex=0;
  State<T> *current;
  State<T> *start;
  State<T> *now;
  double sumCost;
  typename std::vector<State<T> *>::iterator it;
  bool found;
  vector<State<T> *> adj;
  list<State<T>*>* closed = new list<State<T>*>();

 public:
  //check if this node is in closed
  bool inClose(State<pair<int,int>>* s){
    for (auto itr = closed->begin(); itr!=closed->end(); itr++){
      now = *itr;
      if (now==s){
        return true;
      }
    }
    return false;
  }

  //search algorithm
  State<T>* search(Searchable<T> *s) override {
    vector<vector<State<pair<int, int>>*>>  mat = s->getstateMatrix();
    int i;
    int j;
    for (i = 0; i < mat.size(); i++) {
      for (j = 0; j < mat[i].size(); j++) {
        this->initialize(mat[i][j]);
      }
    }

    State<T>* first = s->getInitialState();
    first->setPathCost(first->getCost());
    this->queue.push(first);

    while (!this->queue.empty()) { // run until the queue is empty
      State<T>* currentState = this->queue.front(); // get the root of searchable.
      this->queue.pop();
      this->numOfNodes++;
      //raise the number of index by one
      numOfVisitVertex++;
      this->visited[currentState] = BLACK;
      for (State<T>* child : s->getAdj(currentState)) { // check state's children.
        if (child->getCost() == -1) {
          this->visited.at(child) == BLACK;
          continue;
        }
        if (this->visited.at(child) == WHITE) {
          child->setFather(currentState);
          child->setPathCost(currentState->getPathCost() + child->getCost());
          this->visited.at(child) = GRAY;
          if (child == s->getGoalState()) { // case the children in our goal.
            cout<<"num vertex: "<< this->numOfVisitVertex;
            return s->getGoalState();
          }
          this->queue.push(child);
        }
      }
    }
  }

  //get the number of nudes to now
  int getNumberOfNodesEvaluated() override {
    return this->numOfVisitVertex;
  }
  virtual void pushToDataset(State<T> *state) {
      this->queue.push_back(state);
  }
  virtual void popFromDataset() {
      this->queue.pop_front();
  }

  AbstractSearcher<T>* cloneMe()  {
    return new BFS();
  }
};

#endif //EXGIT__BFS_H_