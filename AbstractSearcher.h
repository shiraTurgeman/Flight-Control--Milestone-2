//
// Created by shira on 23.1.2020.
//

#ifndef EX4PROJECT_ABSTRACTSEARCHER_H
#define EX4PROJECT_ABSTRACTSEARCHER_H

#include <queue>
#include <map>
#include <iostream>
#include "Searcher.h"
#include <unordered_map>
enum color {
  WHITE, GRAY, BLACK
};

/*
 * This class use as comperator to the priority queue.
 * we used the comperator to compare between two states,
 * by their value path from the init state  plus the distance from
 * the state to the goal state.
 */
template<class T>
class myComparator {
 public:
  int operator()(const State<T> *p1, const State<T> *p2) {
    return p1->getPathCost() + p1->getDistance() > p2->getPathCost() + p2->getDistance();
  }
};

template<class T>/*
 * This algorithm is one of the searchers.
 * it search for the solution and work as breadth first search works.
 * we use queue for this algorithm.
 */
class AbstractSearcher : public Searcher<T, State<T> *>{
 protected:
  double numOfNodes;
  std::unordered_map<State<T>*, color> visited;
  std::priority_queue<State<T>*, std::vector<State<T> *>, myComparator<T>> open;
  std::queue<State<T>*> queue;

  /*
   * This func initial all the state as un visited.
   */
  void initialize(State<T> * s) {
    this->visited[s] = WHITE;
  }

  /*
   * This func return the trace from the init to the state sent him.
   * it checks who is the father of each state and go back
   * until he get's to the init state.
   */
  std::vector<State<T> *> *backTrace(State<T> *state) {
    auto trace = new std::vector<State<T> *>;
    while (state != nullptr) {
      trace->push_back(state);
      state = state->getFather();
    }
    return trace;
  }


 public:
  AbstractSearcher() {}

  virtual ~AbstractSearcher()= default;

  virtual State<T> *search(Searchable<T> *s) = 0;

  double getNumOfNodesEvaluated() {
    return this->numOfNodes;
  };

  template<class P, class S>
  AbstractSearcher<P>* cloneMe() {
    return this->cloneMe();
  }


};



#endif //EX4PROJECT_ABSTRACTSEARCHER_H