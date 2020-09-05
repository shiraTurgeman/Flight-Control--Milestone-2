//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_SEARCHERSOLVER_H
#define EXGIT_SEARCHERSOLVER_H

#include <string>
#include "Solver.h"
#include "Searcher.h"

using namespace std;

template<typename P, typename S>
/**
* class for SearcherSolver
**/
class SearcherSolver : public Solver<Searchable<P> *, S> {

  Searcher<P, S> *searcher;
 public:
  explicit SearcherSolver(Searcher<P, S> *searcher) {
    this->searcher = searcher;
  }

  State<P> *solve(Searchable<P> *problem) override {
    //send to the solver
    return this->searcher->search(problem);
  }

  SearcherSolver* clone() override {
    SearcherSolver* solver = new SearcherSolver(searcher->cloneMe());
    return solver;
  }

};

#endif //EXGIT_SEARCHERSOLVER_H