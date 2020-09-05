//
// Created by noa on 17/01/2020.
//

#ifndef EXGIT__ASTAR_H_
#define EXGIT__ASTAR_H_

#include "Searcher.h"
#include "BestFirstSearch.h"
#include <unordered_set>
#include <queue>
#include <stack>
#include <math.h>
#include <unordered_set>
#include "AbstractSearcher.h"
#include <iostream>

#include <list>
using namespace std;



/**
* class for Astar
**/



template<class T>
class AStar : public BestFirstSearch<pair<int,int>> {//Searcher<P, State<P> *>
 private:



 public:
  int numOfVisitVertex;

  int getNumberOfNodesEvaluated() override {
    return 0;
  }


  State<T>* search(Searchable<T> *s) {

    vector<vector<State<pair<int, int>>*>>  mat = s->getstateMatrix();
    int i;
    int j;
    for (i = 0; i < mat.size(); i++) {
      for (j = 0; j < mat[i].size(); j++) {
        this->initialize(mat[i][j]);
      }
    }


    State<T> *first = s->getInitialState();
    first->setPathCost(first->getCost());
    this->open.push(first);

    while (!this->open.empty()) { // until the queue is not empty.
      // get the most lower path cost.
      State<T> *n = this->open.top();
      this->open.pop();
      this->visited.at(n) = BLACK;
      this->numOfNodes++;
      numOfVisitVertex++;
      // check if it is the goal.
      if (n==s->getGoalState()) {
        //cout<<"num vertex"<<numOfVisitVertex;
        return s->getGoalState();
      }
      // get all the neighbors.
      std::vector<State<T> *> succerssors = s->getAdj(n);

      for (State<T> *it : succerssors) { // check for the child of the state.
        if (it->getCost() == -1) {
          continue;
        }
        double currentPathCost = n->getPathCost() + it->getCost();
        if (this->visited.at(it) == WHITE) {
          this->visited.at(it) = GRAY;
          it->setFather(n);
          it->setPathCost(currentPathCost);
          this->open.push(it);

        } else if (currentPathCost < it->getPathCost()) {
          it->setFather(n);
          it->setPathCost(currentPathCost);
          if (this->visited.at(it) == BLACK) {
            this->visited.at(it) = GRAY;
            this->open.push(it);
          }
        }
      }
    }
    return nullptr;



  }

  AbstractSearcher<T>* cloneMe()  {
    return new AStar();
  }

};







#endif //EXGIT__ASTAR_H_