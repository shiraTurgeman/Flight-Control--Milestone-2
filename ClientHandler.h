//
// Created by shira on 12.1.2020.
//

#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_
#include <string>
/**
* Class for ClientHandler
**/

class ClientHandler {
 public:
  virtual ClientHandler* duplicate(){};
  virtual void handleClient(int port) = 0;
  virtual ~ClientHandler(){}
  virtual std::string getSol()=0;

};


#endif //EX4_CLIENTHANDLER_H