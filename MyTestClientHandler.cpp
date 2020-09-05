
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "MyTestClientHandler.h"
#include "Matrix.h"

using namespace std;
bool toRead;

/**
* Class for MyTestClientHandler
**/
//constructor for MyTestClientHandler
MyTestClientHandler::MyTestClientHandler() {};
//this method read from inputStream line by line.
void MyTestClientHandler::handleClient(int port) {
  Matrix *matrix = new Matrix();
  char problemLine[1024] = {0};
  int isRead;
  toRead = true;
  //read line from the server
  while (toRead) {
    isRead = read(port, problemLine, 1024);
    int j;
    if (isRead < 0) {
      cerr << "error with read" << endl;
    }
    if ((strcmp(problemLine, "end") == 0) || (strcmp(problemLine, "end\n") == 0)
        || (strcmp(problemLine, "end\r\n") == 0)) {
      //end of input
      toRead = false;
      break;
    } else {
      matrix->putRowInMatrix(problemLine);
      for(j=0; j<1023;j++){
        problemLine[j]=0;
      }
      //read line from the server
      isRead = read(port, problemLine, 1023);
      if (isRead == -1) {
        cerr << "error with read" << endl;
      } else if ((strcmp(problemLine, "end") == 0) || (strcmp(problemLine, "end\n") == 0)
          || (strcmp(problemLine, "end\r\n") == 0)) {
        //end of input
        toRead = false;
        break;
      }else{
        matrix->putRowInMatrix(problemLine);
        for(j=0; j<1023;j++){
          problemLine[j]=0;
        }
      }
    }

  }
/*
    //print matrix
    for(int t=0;t<matrix->getMatrix().size(); t++){
        for(int y=0;y<matrix->getMatrix()[t].size(); y++){
            cout<<matrix->getMatrix()[t][y]<<", ";
        }
        cout<<endl;
    }
*/
}
//destructor for MyTestClientHandler
MyTestClientHandler::~MyTestClientHandler() {};