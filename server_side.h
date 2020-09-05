//
// Created by shira on 12.1.2020.
//

#ifndef EX4__SERVER_SIDE_H_
#define EX4__SERVER_SIDE_H_

#include "ClientHandler.h"
#include <mutex>
extern bool shouldRun;
extern int countCurrentTreaths;

using namespace std;

namespace server_side {
/**
* Expression Server
*/
class Server {
 public:
  //open the socket to read the client
  virtual void open(int port, ClientHandler *c) = 0;
  //stop the reading from the client
  virtual void stop() = 0;
  //destroctor
  virtual ~Server() {}
};

}

#endif //EX4_SERVER_SIDE_H