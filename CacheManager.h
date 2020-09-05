//
// Created by shira on 12.1.2020.
//

#ifndef EX4__CACHEMANAGER_H_
#define EX4__CACHEMANAGER_H_

#include <string>

using namespace std;
/**
* Class for CacheManager
**/
class CacheManager {
 public:
  //this method find the problem and solution in mapCache
  virtual bool findSolution(string problem) = 0;
  //get solution for the problem from mapCache
  virtual string getSolution(string problem) = 0;
  //save solution in mapCache
  virtual void saveSolution(string problem, string solution) = 0;
  //destructor
  virtual ~CacheManager(){};
};


#endif //EX4_CACHEMANAGER_H