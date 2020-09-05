//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_SEARCHER_H
#define EXGIT_SEARCHER_H

#include "Searchable.h"
/**
* class for Searcher
**/
template<class P, class S>
class Searcher {
 public:
  //the search algorithm.
  virtual S search(Searchable<P> *searchable) = 0;
  //get how many nodes were evaluated by the algorithm
  virtual int getNumberOfNodesEvaluated() = 0;
  virtual Searcher<P,S>* cloneMe() =0;

  virtual ~Searcher() {}
};

#endif //EXGIT_SEARCHER_H