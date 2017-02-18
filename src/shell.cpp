#include <unistd.h>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include "shell.h"
#include "connector.h"
#include "command.h"

using namespace std;

shell::shell(){
    getlogin_r(userName, 128);
    gethostname(hostName, 128);
}

void shell::run(){
    while(true){
        cout << userName << "@" << hostName << "$ "; 
        string getInput;                                //declare a new string getInput
        getline(cin, getInput);                         //getline the string
        stringstream parser(getInput);                  //turn into ss
        list<connector*> cList;                         //declare list of connector pointers.
        string word;
        connector* curr = new head();
        vector<string> cmd;
        parser >> word;
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
                //cout << "checking for error and output word: " << word << endl;
                cmd.push_back(word);
                // for(int i = 0; i < cmd.size(); i++){
                //     cout << "Test: " << cmd.at(i) << endl;
                // }
            }
        }
        command* c = new command(cmd); // makes a new command pointer
        cmd.clear(); //clears vector
        curr->setCommand(c); //sets current connector command to c
        cList.push_back(curr); //push back connector to linked list
        
        list<connector*>::iterator it;
        for(it = cList.begin(); it != cList.end(); it++){
            if((*it)->getType() == "head"){
                (*it)->execute();
            }
            else if((*it)->getType() == "or"){
                if((*it)->getBool() == true){
                    (*it)->execute();
                }
            }
            else if((*it)->getType() == "and"){
                if((*it)->getBool() == false){
                    (*it)->execute();
                }
            }
            else if((*it)->getType() == "semi"){
                (*it)->execute();
            }
        }
    }
}
