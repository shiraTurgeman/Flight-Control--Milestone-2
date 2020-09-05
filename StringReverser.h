//
// Created by shira on 16.1.2020.
//

#ifndef EXGIT_STRINGREVERSER_H
#define EXGIT_STRINGREVERSER_H


#include "Solver.h"
#include <string>
using namespace std;
class StringReverser {
 public:
  //constructor
  StringReverser();
  string solve (string problem);
  // Swap character starting from two corners
  string reverseStr(string& problem);
  //destructor
  ~StringReverser();
};


#endif //EXGIT_STRINGREVERSER_H