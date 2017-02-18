#include "connector.h"
#include "command.h"
using namespace std;

connector::connector(){
    child = NULL;
}

void connector::setCommand(command* cmd){
    child = cmd;
}

void connector::execute(){
    child->execCmd();
}

bool connector::getBool(){
    return child->didCommand();
}

//**********HEAD**********
//constructor for head subclass
head::head(){
    child = NULL;
    type = "head";
}

string head::getType(){
    return type;
}

// bool head::getBool(){
//     return child->didCommand();
// }

//**********OR**********
//constructor for || subclass
opOr::opOr(){
    child = NULL;
    type = "or";
}

string opOr::getType(){
    return type;
}

// bool opOr::getBool(){
//     return child->didCommand();
// }
//**********AND**********
//constructor for && subclass
opAnd::opAnd(){
    child = NULL;
    type = "and";
}

string opAnd::getType(){
    return type;
}

// bool opAnd::getBool(){
//     return child->didCommand();
// }

//**********SEMI**********
//constructor for || subclass
opSemi::opSemi(){
    child = NULL;
    type = "semi";
}

string opSemi::getType(){
    return type;
}

// bool opSemi::getBool(){
//     return child->didCommand();
// }
