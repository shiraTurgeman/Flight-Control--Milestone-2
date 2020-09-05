//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_SOLVER_H
#define EXGIT_SOLVER_H

/**
* class for Solver
**/
template<typename P, typename S>
class Solver {
  P problem;
  S solution;
 public:
  virtual S solve(P problem) = 0;
  virtual Solver<P,S> *clone() =0;

  virtual ~Solver() {}
};

#endif //EXGIT_SOLVER_H