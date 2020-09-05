cmake_minimum_required(VERSION 3.15)
project(ex4Submit)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

add_executable(ex4Submit main.cpp AStar.h BestFirstSearch.h BFS.h DFS.h CacheManager.h ClientHandler.h FileCacheManager.cpp FileCacheManager.h Matrix.cpp Matrix.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h Searchable.h Searcher.h SearcherSolver.h server_side.h Solver.h State.h StringReverser.cpp StringReverser.h MyParallelServer.h MyParallelServer.cpp boot.h MyClientHandler.h AbstractSearcher.h)