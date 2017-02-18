#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <iostream>
#include <string>
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
    virtual string getType() = 0;
    bool getBool();
  protected:
    command* child;
};

class head : public connector
{
  public:
    head();
    string getType();
    // bool getBool();
  private:
    string type;
};

class opOr : public connector
{
  public:
    opOr();
    string getType();
    // bool getBool();
  private:
    string type;
};

class opAnd : public connector
{
  public:
    opAnd();
    string getType();
    // bool getBool();
  private:
    string type;
};

class opSemi : public connector
{
  public:
    opSemi();
    string getType();
    // bool getBool();
  private:
    string type;
};

#endif
