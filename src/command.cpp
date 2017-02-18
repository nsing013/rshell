#include "command.h"

using namespace std;

command::command(vector<string> cmd){
    input = cmd;
    failedExecute = true;
    arguments = new char*[input.size() + 1];
}

void command::parse(){
    if(input.size() == 0){
        cout << "vector<string> is empty" << endl;
    }
    else if(input.at(0) == "exit"){ //checks to see if user typed exit
        exit(-1); //exits
    }
    else{ //otherwise, send commands to arguments char array
        for(unsigned i = 0; i < input.size(); i++){
            arguments[i] = (char*)input.at(i).c_str();
        }
        arguments[input.size()] = NULL;
    }
}
void command::execCmd(){
    this->parse();
    pid_t pid = fork();
    if (pid == 0){ //CHILD
        if (execvp(arguments[0], arguments) == -1){
            perror ("exec");
        }
    }
    if (pid > 0){ //PARENT
        if ( wait(0) == -1){
            perror ("wait");
        }
    }
    if (pid < 0){
        cout << "fork() failed!\n";
        failedExecute = false;
    }
}

bool command::didCommand(){
    return this->failedExecute;
}

