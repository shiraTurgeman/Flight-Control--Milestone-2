//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_DFS_H
#define EXGIT_DFS_H

#include "Searcher.h"
#include <unordered_set>
#include <queue>
#include <stack>
#include "AbstractSearcher.h"
#include "list"
using namespace std;

/**
* class for DFS
**/
template<class T>
class DFS : public AbstractSearcher<T> {
 private:

  //variable for the algorithm
  int numOfVisitVertex;
  bool found;
  double sumCost = 0;
  typename std::vector<State<T> *>::iterator it;
  list<State<T> *> *closed = new list<State<T> *>();
  stack<State<T> *> statesStack;
  vector<State<T> *> adj;
  State<T> *current;
  State<T> *start;
  State<T> *now;
  State<T> *returnThis;

 public:

  //this function iterates over the close list.
  bool inClose(State<pair<int, int>> *s) {
    for (auto itr = closed->begin(); itr != closed->end(); itr++) {
      now = *itr;
      if (now == s) {
        return true;
      }
    }
    return false;
  }

  //search function.
  State<T> *search(Searchable<T> *searchable) override {
    //initialize the start variable
    start = searchable->getInitialState();
    start->setPathCost(start->getCost());
    statesStack.push(start);
    //while the queue isn't empty go over the queue
    while (!statesStack.empty()) {
      current = statesStack.top();
      statesStack.pop();
      numOfVisitVertex++;
      closed->push_front(current);
      if (current == searchable->getGoalState()) {
        cout << "num vertex" << numOfVisitVertex;
        return current;
      }
      adj = searchable->getAdj(current);
      State<pair<int, int>> *now;
      for (int k = adj.size() - 1; k >= 0; k--) {
        now = adj[k];
        if ((now->getCost() != -1) && (!inClose(now))) {
          now->setFather(current);
          now->setPathCost(current->getPathCost() + now->getCost());
          statesStack.push(now);
        }
      }
    }
  }

  int getNumberOfNodesEvaluated() override {
    return this->numOfVisitVertex;
  }

 protected:

  virtual void pushToDataset(State<T> *state) {
    this->statesStack.push(state);
  }

  virtual void *popFromStucture() {
    this->statesStack.pop();
  }

  virtual bool isEmptyStructure() {
    this->statesStack.empty();
  }

  template<class P, class S>
  AbstractSearcher<T>* cloneMe()  {
    return new DFS();
  }
};

#endif //EXGIT_DFS_H