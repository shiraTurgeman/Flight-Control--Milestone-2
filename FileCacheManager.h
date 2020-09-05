//
// Created by shira on 12.1.2020.
//

#ifndef EX4__FILECACHEMANAGER_H_
#define EX4__FILECACHEMANAGER_H_

#include <map>
#include "CacheManager.h"
/**
* Class for FileCacheManager
**/
class FileCacheManager : public CacheManager {
 private:
  map <string,string> cache;
  int sizeCache = 5;
  string solution;
 public:
  //constructor
  FileCacheManager();
  //this method find the problem and solution in mapCache
  bool findSolution(string problem);
  //get solution for the problem from mapCache
  string getSolution(string problem);
  //save solution in mapCache
  void saveSolution(string problem, string solution);
  //save problem in files
  void saveSolutionInFile(string problem, string solution);
  //save five problems in cache map
  void saveSolutionInMap(string problem, string solution);
  //destructor
  ~FileCacheManager();
};


#endif //EX4_FILECACHEMANAGER_H