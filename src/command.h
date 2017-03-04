#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
/*this is the Command BASE CLASS and it has 2 SUBCLASSES
"BuiltIn" and "Executable" The BuiltIn has another subclass 
called "Exit" which is handles the Built In Command Exit */

class command{
  public:
    command(vector<string> cmd);
    void parse();
    void execCmd();
    bool didCommand();
  private:
    vector<string> input;
    bool failedExecute;
    char** arguments;
};

#endif