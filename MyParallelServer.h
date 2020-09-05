

//
// Created by shira on 20.1.2020.
//
#ifndef EX4PROJECT_MYPARALLELSERVER_H
#define EX4PROJECT_MYPARALLELSERVER_H
#include "server_side.h"
#include <mutex>
#include <sys/time.h>
#include <vector>


#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <vector>
#include <thread>

using namespace std;
using namespace server_side;

/**
* class for MyParallelServer
**/
class MyParallelServer : public server_side::Server {
  static void *loop(void *arg);

 protected:
  bool parBool = false;

  void stop() override;
  static void *serverThread(void *arg);
  void unique(int sock, bool *stop, ClientHandler *client);

 public:
  //mutex N;

  void open(int port, ClientHandler *c) override ;
  //vector<pthread_t> threads;

};
//stop the reading.
typedef struct {
  int socket;
  ClientHandler *client;
} clientDat;

//create the struct to fold the data information
typedef struct {
  MyParallelServer *server;
  int port;
  bool *stop_server;
  ClientHandler *client;
} serverObj;

#endif //EX4PROJECT_MYPARALLELSERVER_H
