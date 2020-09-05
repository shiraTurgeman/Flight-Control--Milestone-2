//
// Created by shira on 12.1.2020.
//

#include <fstream>
#include <iostream>
#include "FileCacheManager.h"
#include <map>
#include <mutex>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

/**
* Class for FileCacheManager
**/
//constructor
mutex v;
FileCacheManager::FileCacheManager(){
  map <string, string> cache;
}
//this method find the problem and solution in mapCache
bool FileCacheManager::findSolution(string problem){
  if (cache.count(problem))
  {
    cout<<"find";
    //problem exist in catch
    return true;
  }
  else{
    int numHash = hash<string>{}(problem);
    string nameFile = to_string(numHash)+".txt";
    cout<<"hash map:  "<<numHash;
    fstream myfile(nameFile);
    if (myfile){
      cout<<"found in file";
      return true;
    }else{
      cout<<"not found";
      //the problem doesn’t exist both in main and filesystem
      return false;
    }
  }
}

//get solution for the problem from mapCache
string FileCacheManager::getSolution(string problem){
  if (cache.count(problem))
  {
    //problem exist in catch
    return cache[problem];
  }
  else{
    //create number for hash map for the solotion
    int numHash = hash<string>{}(problem);
    string nameFile = to_string(numHash)+".txt";
    cout<<"hash map:  "<<numHash;
    v.lock();
    string item_name;
    ifstream myfile;
    myfile.open(nameFile);
    string solution;
    if (myfile){
      getline(myfile, solution);
      cout << "line:" << solution << std::endl;
    }else{
      //the problem doesn’t exist both in main and filesystem
      throw"an error";
    }
    v.unlock();
    myfile.close();
    return solution;
  }
}
//save solution in mapCache and in file
void FileCacheManager::saveSolution(string problem, string solution){
  saveSolutionInFile(problem, solution);
  saveSolutionInMap(problem, solution);
}
//save problem in files
void FileCacheManager::saveSolutionInFile(string problem, string solution){
  //name of file
  string stringProblem=problem;
  int numHash = hash<string>{}(stringProblem);
  string nameFile = to_string(numHash)+".txt";
  cout<<"hash file:  "<<numHash;
  //open new file
  ofstream myfile;
  myfile.open(nameFile, std::ios::out | ios::binary);
  unsigned int size = solution.size();

  if (!myfile.is_open()){
    cout<<"error with open file";
  }
  myfile.write(solution.c_str(), size);

  myfile.close();
}
//save five problems in cache map
void FileCacheManager::saveSolutionInMap(string problem, string solution){
  if (!cache.count(problem))
  {
    if (cache.size()==sizeCache){
      //the cache is full, need to delete one problem and insert the new problem
      cache.erase(cache.begin());
      cache.insert({problem, solution});
    }else{
      cache.insert({problem, solution});
    }
  }

  for(auto it = cache.cbegin(); it != cache.cend(); ++it)
  {
    std::cout <<"----- "<< it->first << " " << it->second << " " <<"+++"<< "\n";
  }
}
//destructor
FileCacheManager::~FileCacheManager(){};