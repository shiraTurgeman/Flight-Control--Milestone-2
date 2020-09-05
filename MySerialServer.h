//
// Created by shira on 12.1.2020.
//

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_

#include "server_side.h"
//#include "ClientHandler.h"
#include <mutex>

using namespace std;
using namespace server_side;
extern mutex mutexOne;
/**
* class for MySerialServer
**/
class MySerialServer : public server_side::Server {
 public:
  //constroctor
  MySerialServer();
  //method open the client
  void open(int port, ClientHandler *c);
  //stop the reading
  void stop();
  //create a loop that accept a client one after the other
  void runLoop(ClientHandler *c, int socketSer, struct sockaddr_in addressSer, int port);
  //destrcotor
  ~MySerialServer();
};

#endif //EX4_MYSERIALSERVER_H