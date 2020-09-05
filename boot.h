//
// Created by shira on 14.1.2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include <iostream>
#include <algorithm>
#include "Searchable.h"
#include "Searcher.h"
#include "DFS.h"
#include "BFS.h"
#include "AStar.h"
#include "BestFirstSearch.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "StringReverser.h"
#include "Matrix.h"
#include "SearcherSolver.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"

namespace boot {
/**
* class for Main
**/
class Main {
 public:
  //Main();

  static void main(int argc, char const *argv[]) {
    int port = stoi(argv[1]);


    Searcher<pair<int, int>, State<pair<int, int>> *> *searcher;
    searcher = new AStar<pair<int, int>>();
    auto *A = new MyParallelServer();
    CacheManager *cacheManager;
    cacheManager = new FileCacheManager();

    Solver<Searchable<pair<int, int>> *, State<pair<int, int>> *> *solver;
    solver = new SearcherSolver<pair<int, int>, State<pair<int, int>> *>(searcher);
    //ClientHandler *B = new MyClientHandler<Searchable<pair<int, int>>*, State<pair<int, int>>*>(solver);
    ClientHandler *clientHandler = new MyClientHandler<Searchable<pair<int, int>> *, State<pair<int, int>> *>(
        solver, cacheManager);
    A->open(port, clientHandler);

    string str = "project";
    StringReverser *rev = new StringReverser();
    string strrev = rev->solve(str);

    cout << "str: " << strrev << endl;

  }
};
}

#endif //EX4_BOOT_H
