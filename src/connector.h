#include <iostream>
#include "command.h"
using namespace std;

/* this class is the Base Connector class. It has 4 children.
"||" "&&" ";" "head". */

class connector
{
  public: 
    connector();
    void setCommand(command* cmd);
    void execute();
  protected:
    command* child;
};

class head : public connector
{
  public:
    head();
};

class opOr : public connector
{
  public:
    opOr();
};

class opAnd : public connector
{
  public:
    opAnd();
};

class opSemi : public connector
{
  public:
    opSemi();
};
