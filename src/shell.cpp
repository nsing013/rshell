#include <unistd.h>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include "shell.h"
#include "connector.h"

using namespace std;

shell::shell(){
    getlogin_r(userName, 128);
    gethostname(hostName, 128);
}

void shell::run(){
    while(true){
        cout << userName << "@" << hostName << "$ ";
        string getInput; //declare a new string getInput
        getline(cin, getInput); //getline the string
        stringstream parser(getInput); //turn into ss
        list<connector*> cList; //declare list of connector pointers.
        string word;
        connector* curr = new head();
        vector<string> cmd;
        while(parser >> word){
            if(word == ";"){
              cList.push_back(curr);
              curr = new opSemi();
            }
            else if(word == "||"){
              cList.push_back(curr);
              curr = new opOr();
            }
            else if(word == "&&"){
              cList.push_back(curr);
              curr = new opAnd();
            }
            else{
                cmd.push_back(word);
            }
        }
        command* c = new command(cmd); // makes a new command pointer
        curr->setCommand(c); //sets current connector command to c
        cList.push_back(curr); //push back connector to linked list
        
    }
}