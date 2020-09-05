//
// Created by shira on 12.1.2020.
//

#include "MySerialServer.h"

//#include "ClientHandler.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mutex>
#include <sstream>
#include "MyClientHandler.h"

using namespace std;
mutex mutexOne;
bool timeOut;
bool ifClose = true;

//constroctor
MySerialServer::MySerialServer() {};

//method open the client
void MySerialServer::open(int port, ClientHandler *c) {
  //creating new socket
  int socketServer = socket(AF_INET, SOCK_STREAM, 0);
  if (socketServer == -1) {
    //cant create socket
    cerr << "cant create socket" << std::endl;
  }
  //create the object for the bind
  struct sockaddr_in addressSer;
  addressSer.sin_family = AF_INET;
  addressSer.sin_addr.s_addr = INADDR_ANY;
  addressSer.sin_port = htons(port);
  //bind the socket to ip
  int binding = bind(socketServer, (struct sockaddr *) &addressSer, sizeof(addressSer));
  if (binding == -1) {
    std::cerr << "cant bind socket to ip" << std::endl;
  }
  //listen to the port
  int listenning = listen(socketServer, 5);
  if (listenning == -1) {
    std::cerr << "cant listen to ip" << std::endl;
  }

  //open thread and sent to function that create accept
  std::thread loopThread(&MySerialServer::runLoop, this, c, socketServer, addressSer, port);
  loopThread.join();
}

//stop the reading
void MySerialServer::stop() {
  ifClose = false;
}

//create a loop that accept a client one after the other
void MySerialServer::runLoop(ClientHandler *c, int socketServer, struct sockaddr_in addressSer, int port) {
  //defining time out
  struct timeval tv;
  tv.tv_sec = 120;
  setsockopt(socketServer, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof(tv));
  //run until 2 minutes that there are no clients
  while (ifClose) {
    //lock with mutex
    mutexOne.lock();
    cout << "###accept" << endl;
    int acc = accept(socketServer, (struct sockaddr *) &addressSer, (socklen_t *) &addressSer);
    if (acc == -1) {
      std::cerr << "cant accept client" << std::endl;
      stop();
    } else {
      //call client handler
      c->handleClient(acc);
      //send to client
      string send=c->getSol();
      //send(socketServer, send.c_str(), send.length(), 0);

      int is_sent = write(acc, send.c_str(),send.length());
      if (is_sent < 0){
        cout << "problem to send the client"<<endl;
      }
    }

    //unlock the mutex
    mutexOne.unlock();
  }
}

//destrcotor
MySerialServer::~MySerialServer() {};