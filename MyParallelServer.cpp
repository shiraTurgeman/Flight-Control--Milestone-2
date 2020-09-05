//
// Created by noa on 19/01/2020.
//
#include "MyParallelServer.h"
#include "MyTestClientHandler.h"

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include "pthread.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mutex>
#include <sstream>
#include <vector>
#include <strings.h>
typedef int i;
using namespace std;
mutex n;
//create the object of the client
void *MyParallelServer::loop(void *arg) {
  clientDat *clientDatOne = (clientDat *) arg;
 // n.lock();
  clientDatOne->client->handleClient(clientDatOne->socket);
 // n.unlock();
  // delete (clientDatOne);
  return nullptr;
}
void MyParallelServer::unique(int sock, bool *stop, ClientHandler *client){
  int socketFd = sock;
  int newsockfd;
  int clilen;
  //vector<pthread_t> threads;
  struct sockaddr_in serv_addr, cli_addr;

  listen(socketFd, 10);
  clilen = sizeof(cli_addr);
  while (true) {
    newsockfd = accept(socketFd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd < 0) {
      if (*stop) {
        break;
      }
      if (errno == EWOULDBLOCK) {
        continue;
      }
      perror("Failed accepting client");
      exit(1);
    }
    clientDat *clientDatOne;
    clientDatOne = new clientDat();
    clientDatOne->socket = newsockfd;

    //create clone for client
    clientDatOne->client = client->duplicate();

    //operate the thread
    pthread_t single_thread;
    pthread_create(&single_thread, nullptr, loop, clientDatOne);

    //threads.push_back(single_thread);

    timeval timeout;
    timeout.tv_sec = 120;
    timeout.tv_usec = 0;
    setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
  }
}
//open the client
void MyParallelServer::open(int port, ClientHandler *c) {
  cout<<"per"<<endl;
  serverObj *params;
  params = new serverObj();
  params->server = this;
  params->port = port;
  params->client = c;
  params->stop_server = &parBool;
  pthread_t single_thread;
  pthread_create(&single_thread, nullptr, serverThread, params);
  pthread_join(single_thread, nullptr);
}
//stop the reading.
void MyParallelServer::stop() {
  parBool = true;
}
void *MyParallelServer::serverThread(void *arg) {
  serverObj *server= (serverObj *)arg;
  int sockFd;
  struct sockaddr_in serveAddr;

  sockFd= socket(AF_INET,SOCK_STREAM, 0);
  if (sockFd<0){
    perror(("fail in opening socket"));
    exit(1);
  }

  bzero((char*)&serveAddr, sizeof(serveAddr));

  serveAddr.sin_family=  AF_INET;
  serveAddr.sin_addr.s_addr= INADDR_ANY;
  serveAddr.sin_port= htons(server->port);

  if (bind(sockFd, (struct sockaddr *) &serveAddr, sizeof(serveAddr)) < 0) {
    perror("Failed binding socket");
    exit(1);
  }
  server->server->unique(sockFd, server->stop_server, server->client);

  close(sockFd);
  delete(server->client);
  delete(server);
  return nullptr;
}
//destroctor
//MyParallelServer::~MyParallelServer() {};

