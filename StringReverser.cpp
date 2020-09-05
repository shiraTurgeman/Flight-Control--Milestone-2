//
// Created by shira on 16.1.2020.
//

#include "StringReverser.h"

/**
* class for StringReverser
**/
//constructor
StringReverser::StringReverser(){};
// Function to reverse a string
string StringReverser::reverseStr(string& reverseProblem)
{
  int n = reverseProblem.length();
  // Swap character starting from two corners
  for (int i = 0; i < n / 2; i++)
    swap(reverseProblem[i], reverseProblem[n - i - 1]);
  return reverseProblem;
}

string StringReverser::solve (string problem){
  string reverseProblem = problem;
  reverseStr(reverseProblem);
  return reverseProblem;
}
//destructor
StringReverser::~StringReverser(){};