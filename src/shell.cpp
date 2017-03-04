#include <unistd.h>
#include <string>
#include <cstring>
#include <list>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include "shell.h"
#include "connector.h"
#include "command.h"

using namespace std;

void testCommand(string test, string path){
    struct stat s;                                       //declare Stat S
    stat(path.c_str(), &s);                              //make stat
    if(test == "-f" || test == "-d"){
        if(S_ISDIR(s.st_mode) && test == "-d"){
            cout << "(True)" << endl; 
        }
        else if(S_ISREG(s.st_mode) && test == "-f"){
            cout << "(True)" << endl;
        }
        else{
            cout << "(False)" << endl;
        }
    }
    else if(test == "-e"){
        if(S_ISDIR(s.st_mode) || S_ISREG(s.st_mode)){
            cout << "(True)" << endl;
        }
        else{
            cout << "(False)" << endl;
        }
    }
}

shell::shell(){
    getlogin_r(userName, 128);
    gethostname(hostName, 128);
}

void shell::run(){
    while(true){
        cout << userName << "@" << hostName << "$ "; 
        string getInput;                                //declare a new string getInput
        getline(cin, getInput);                         //getline the string
        if(getInput == ""){                             //*****THIS CHECKS TO SEE IF USER ENTERED NOTHING*****
            continue;
        }
        //stringstream parser(getInput);                  //turn into ss
        //string word;
        list<connector*> cList;                         //declare list of connector pointers.
        connector* curr = new head();
        vector<string> cmd;
        
        
        // //we need to use strTok for future programs
        // char* input = strdup(getInput.c_str()); //this is so theres no problem assigning a const char* to a char*
        // char* token = strtok(input, ";&|"); // check the command for these connectors using strtok
        // while(token != NULL)
        // {
        //     cout << token << endl;
        //     token = strtok(NULL, ";&|");
        // }    
        
        //PARENTHESIS START HERE 
        char* input = strdup(getInput.c_str());     //this is so theres no problem assigning a const char* to a char*
        char* token = strtok(input, "()");          // check the command for these connectors using strtok
        
        while(token != NULL)
        {
            //cout << "Token: " << token << endl; //debug
            string str(token);
            stringstream parser(str);                     //turn into ss
            string word;
            
        while(parser >> word){
            if(word.at(word.size() - 1) == ';'){    //check if semi colon
                if(word.size() > 1){
                    cmd.push_back(word.substr(0, word.size() - 1));
                }
                command* c = new command(cmd);      //makes new command pointer with cmd vector
                curr->setCommand(c);                //sets curr command as c
                cList.push_back(curr);              //push back curr to list
                cmd.clear();                        //clear the cmd vector
                curr = new opSemi();                //makes a new semi connector
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
            else if(word == "]"){
                continue;
            }
            else if(word == "test" || word == "["){
                //cout << "test for word" << word << endl; //TESTING
                parser >> word;
                //cout << "New test for word" << word << endl; // testing for second parsed word
                if(word == "-e" || word == "-f" || word == "-d"){ //checks if the file/directory exists
                    string path;
                    parser >> path;
                    //cout << "New test for path" << path << endl; //test for path
                    testCommand(word, path);
                }
                else{
                    string e = "-e";
                    //cout << "unchanged word" << word << endl;
                    testCommand(e, word);
                }
            }
            else{
                //cout << "checking for error and output word: " << word << endl;
                cmd.push_back(word);
                // for(int i = 0; i < cmd.size(); i++){
                //     cout << "Test: " << cmd.at(i) << endl;
                // }
            }
        }
        
        if(!cmd.empty()){
            command* c = new command(cmd);          // makes a new command pointer
            cmd.clear();                            //clears vector
            
            curr->setCommand(c);                    //sets current connector command to c
            cList.push_back(curr);                  //push back connector to linked list
        }
        
        list<connector*>::iterator it; //iterator for navigating list
        for(it = cList.begin(); it != cList.end(); it++){ //forloop through list
            if((*it)->getType() == "head"){
                (*it)->execute();
            }
            else if((*it)->getType() == "or"){
                if((*it)->getBool() == false){
                    (*it)->execute();
                }
            }
            else if((*it)->getType() == "and"){
                if((*it)->getBool() == true){
                    (*it)->execute();
                }
            }
            else if((*it)->getType() == "semi"){
                (*it)->execute();
            }
            //cout << "Type: " << (*it)->getType() << endl;
            //cout << "Bool: " << (*it)->getBool() << endl;
            
            //string Type = (*it)->getType();
            //bool Bool = (*it)->getBool();
        }
        cList.clear();
        token = strtok(NULL, "()");
        }
    }
}