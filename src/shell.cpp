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
        
        while(parser >> word){
            if(word == ";"){ //check if semi colon
                command* c = new command(cmd); //makes new command pointer with cmd vector
                curr->setCommand(c); //sets curr command as c
                cList.push_back(curr); //push back curr to list
                cmd.clear(); //clear the cmd vector
                curr = new opSemi(); //makes a new semi connector
            }
            else if(word == "||"){
                command* c = new command(cmd); //check if OR
                curr->setCommand(c);
                cList.push_back(curr);
                cmd.clear();
                curr = new opOr(); //makes a new OR connector
            }
            else if(word == "&&"){
                command* c = new command(cmd); //check if AND
                curr->setCommand(c);
                cList.push_back(curr);
                cmd.clear();
                curr = new opAnd(); //makes a new AND connector
            }
            else if(word.at(0) == '#'){ //CHEKCS TO SEE IF USER ENTERED COMMENT
                break;
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
        
        list<connector*>::iterator it; //iterator for navigating list
        for(it = cList.begin(); it != cList.end(); it++){ //forloop through list
            if((*it)->getType() == "head"){ //checks to see if the type is head connector
                (*it)->execute(); //if so execute
            }
            else if((*it)->getType() == "or"){ //checks to see if type is OR connector
                if((*it)->getBool() == false){
                    (*it)->execute();
                }
            }
            else if((*it)->getType() == "and"){ //checks to see if type is AND connector
                if((*it)->getBool() == true){
                    (*it)->execute();
                }
            }
            else if((*it)->getType() == "semi"){ //checks to see if type is SEMI conductor
                (*it)->execute();
            }
        }
        cList.clear();
    }
}
