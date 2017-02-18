#include "connector.h"
#include "command.h"
using namespace std;

connector::connector(){
    pair = NULL;
}

void connector::setCommand(command* cmd){
    pair = cmd;
}

void connector::execute(){
    child->execCmd();
}

//**********HEAD**********
//constructor for head subclass
head::head(){
    child = NULL;
}

//**********OR**********
//constructor for || subclass
opOr::opOr(){
    child = NULL;
}

//**********AND**********
//constructor for && subclass
opAnd::opAnd(){
    child = NULL;
}

//**********SEMI**********
//constructor for || subclass
opSemi::opSemi(){
    child = NULL;
}
