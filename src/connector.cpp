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

int connector::getPipefd()
{
    return child->didPipefd();
}

void connector::setPipefd(int fd)
{
    child-> doSetPipefd(fd);
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

//**********OR**********
//constructor for || subclass
opOr::opOr(){
    child = NULL;
    type = "or";
}

string opOr::getType(){
    return type;
}

//**********AND**********
//constructor for && subclass
opAnd::opAnd(){
    child = NULL;
    type = "and";
}

string opAnd::getType(){
    return type;
}

//**********SEMI**********
//constructor for ; subclass
opSemi::opSemi(){
    child = NULL;
    type = "semi";
}

string opSemi::getType(){
    return type;
}

// //******INPUT-REDIRECTION*****
// //constructor for < subclass
// opInputRed::opInputRed(){
//     child = NULL;
//     type = "input redirection";
// }

// string opInputRed::getType(){
//     return type;
// }

// //******OUTPUT-REDIRECTION*****
// //constructor for > subclass
// opOutputRed::opOutputRed(){
//     child = NULL;
//     type = "output redirection";
// }

// string opOutputRed::getType(){
//     return type;
// }

// //******APPEND OUTPUT-REDIRECTION*****
// //constructor for >> subclass
// opAppendOutputRed::opAppendOutputRed(){
//     child = NULL;
//     type = "append output redirection";
// }

// string opAppendOutputRed::getType(){
//     return type;
// }

//*********PIPING**********
//constructor for | subclass
opPipe::opPipe(){
    child = NULL;
    type = "pipe";
}

string opPipe::getType(){
    return type;
}
