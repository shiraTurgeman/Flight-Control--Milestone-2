//
// Created by shira on 12.1.2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_

#include "ClientHandler.h"
extern bool toRead;


/**
* Class for MyTestClientHandler
**/
class MyTestClientHandler : public ClientHandler {
 public:
  //constructor for MyTestClientHandler
  MyTestClientHandler();
  //this method read from inputStream line by line.
  void handleClient(int port);
  //destructor for MyTestClientHandler
  ~MyTestClientHandler();
};


#endif //EX4_MYTESTCLIENTHANDLER_H