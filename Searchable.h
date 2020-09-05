//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_SEARCHABLE_H
#define EXGIT_SEARCHABLE_H

#include <vector>
#include "State.h"
/**
* class for Searchable
**/
template <typename P>
class Searchable {
 public:
  virtual vector<vector<State<pair<int, int>>*>>  getstateMatrix()=0;
  //get the initial state
  virtual State<P>* getInitialState() = 0;
  //get the goal state
  virtual State<P>* getGoalState() = 0;
  //get the neighbors list
  virtual vector<State<P>*> getAdj(State<P>* s)=0;
  //check if its the goal state
  virtual bool isGoalState(State<P>*)=0;
};


#endif //EXGIT_SEARCHABLE_H