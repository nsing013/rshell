#include <unistd.h>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <stack> //evaluating expressions
#include <string.h>
#include "shell.h"
#include "connector.h"
#include "command.h"

using namespace std;

shell::shell(){
    getlogin_r(userName, 128);
    gethostname(hostName, 128);
}

void shell::run()
{
    while(true)
    {
        cout << userName << "@" << hostName << "$ "; 
        string getInput;                                //declare a new string getInput
        getline(cin, getInput);                         //getline the string
        
        //EMPTY COMMAND
        if(getInput == "") 
        {                             
            continue;                                   //just in case fool doesnt enter anything
        }
        
        list<connector*> cList;                         //declare list of connector pointers.
        connector* curr = new head();
        vector<string> cmd;                             //empty vector
        
        //PARENTHESIS
        char* input = strdup(getInput.c_str()); //this is so theres no problem assigning a const char* to a char*
        char* token = strtok(input, "()"); // check the command for these connectors using strtok
        
        while(token != NULL)
        {
            string str(token);
            stringstream parser(str);                   //turn into ss
            string word;
            string iFile = "";                          //honestly most commands will not even use these, only for redirection 
            string oFile = "";
            bool append = false;                        //used specifically for output redirection
            
            
            while(parser >> word)
            {
                bool pipe = false;
                
                //SEMICOLON
                if(word.at(word.size() - 1) == ';')
                {    
                    if(word.size() > 1)
                    {
                        cmd.push_back(word.substr(0, word.size() - 1));
                    }
                    command* c = new command(cmd, iFile, oFile, append, pipe); //makes new command pointer with cmd vector, passedExecution set to true every time
                    curr->setCommand(c);                //sets curr command as c
                    cList.push_back(curr);              //push back curr to list
                    cmd.clear();                        //clear the cmd vector
                    curr = new opSemi();                //makes a new semi connector
                }
                //OR
                else if(word == "||")
                {
                    command* c = new command(cmd, iFile, oFile, append, pipe);
                    curr->setCommand(c);
                    cList.push_back(curr);
                    cmd.clear();
                    curr = new opOr();                  //makes a new OR connector
                }
                //AND
                else if(word == "&&")
                {
                    command* c = new command(cmd, iFile, oFile, append, pipe);
                    curr->setCommand(c);
                    cList.push_back(curr);
                    cmd.clear();
                    curr = new opAnd();                 //makes a new AND connector
                }
                //COMMENT
                else if(word.at(0) == '#')
                {
                    break;
                }
                //LEFT BRACE
                else if(word == "[")
                {
                     cmd.push_back("test");
                }
                //RIGHT BRACE
                else if(word == "]")
                {
                    continue;                           //ignore the damn right bracket, no one likes you anyways -_-
                }
                //INPUT REDIRECTION
                else if(word == "<")
                {
                    parser >> iFile;                    //takes whatever filename user types in as input
                }
                //OUTPUT REDIRECTION
                else if(word == ">")
                {
                    parser >> oFile;                    //takes whatever filename user types to output to
                }
                //APPENDED OUTPUT REDIRECTION
                else if(word == ">>")
                {
                    parser >> oFile;
                    append = true;
                }
                //PIPE
                else if(word == "|")
                {
                    pipe = true;
                    command* c = new command(cmd, iFile, oFile, append, pipe);
                    curr->setCommand(c);
                    cList.push_back(curr);
                    cmd.clear();
                    curr = new opPipe();                  //makes a new OR connector
                }
                //REGULAR COMMAND - could be single command or command in between connectors
                else
                {
                    cmd.push_back(word);                //push back current word onto the command vector
                }
            }
            
            if(!cmd.empty())
            {
                command* c = new command(cmd, iFile, oFile, append, false); // makes a new command pointer
                cmd.clear();                            //clears vector
                curr->setCommand(c);                    //sets current connector command to c
                cList.push_back(curr);                  //push back connector to linked list
            }
            
            list<connector*>::iterator it;               //iterator for navigating list
            bool lastPassed = true;                      //keeps track of whether the previous command passed or not, clutch!!
            int lastPiped = -1;
            //WHEN TO EXECUTE COMMANDS
            for(it = cList.begin(); it != cList.end(); it++) //forloop through list
            { 
                //cout << "lastPiped: " << lastPiped << endl;
                if(lastPiped > 0)
                {
                    (*it)->setPipefd(lastPiped);
                }
                if((*it)->getType() == "head")
                {
                    (*it)->execute();
                }
                else if((*it)->getType() == "or")
                {
                    if(lastPassed == false)             //only execute if previous command was false
                    { 
                        (*it)->execute();
                    }
                }
                else if((*it)->getType() == "and")
                {
                    if(lastPassed == true)              //only execute if previous command was true
                    { 
                        (*it)->execute();
                    }
                }
                else if((*it)->getType() == "semi")
                {
                    (*it)->execute();
                }
                // else if((*it)->getType() == "input redirection")
                // {
                //     (*it)->execute();
                // }
                // else if((*it)->getType() == "output redirection")
                // {
                //     (*it)->execute();
                // }
                // else if((*it)->getType() == "append output redirection")
                // {
                //     (*it)->execute();
                // }
                else if((*it)->getType() == "pipe")
                {
                    (*it)->execute();
                }
                
                lastPassed = (*it)->getBool();  //need this or the lastPassed will be reset to false every time executing incorrect statements
                lastPiped = (*it)->getPipefd();
            }
            cList.clear();
            token = strtok(NULL, "()"); 
        }
    }
}

