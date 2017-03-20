#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <iostream>
#include <string>
#include "command.h"
using namespace std;

/* this class is the Base Connector class. It has 8 children.
"||" "&&" ";" "head" "<" ">"  ">>" "|" */

class connector
{
  public: 
    connector();
    void setCommand(command* cmd);
    void execute();
    virtual string getType() = 0;
    bool getBool();
    int getPipefd();
    void setPipefd(int fd);
  protected:
    command* child;
};

class head : public connector
{
  public:
    head();
    string getType();
  private:
    string type;
};

class opOr : public connector
{
  public:
    opOr();
    string getType();
  private:
    string type;
};

class opAnd : public connector
{
  public:
    opAnd();
    string getType();
  private:
    string type;
};

class opSemi : public connector
{
  public:
    opSemi();
    string getType();
  private:
    string type;
};

// class opInputRed : public connector
// {
//   public:
//     opInputRed();
//     string getType();
//   private:
//     string type;
// };

// class opOutputRed : public connector
// {
//   public:
//     opOutputRed();
//     string getType();
//   private:
//     string type;
// };

// class opAppendOutputRed : public connector
// {
//   public:
//     opAppendOutputRed();
//     string getType();
//   private:
//     string type;
// };

class opPipe : public connector
{
  public:
    opPipe();
    string getType();
  private:
    string type;
};

#endif
