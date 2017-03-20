#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#include "command.h"

using namespace std;

bool testCommand(string test, string path)
{
    struct stat s;
    if(stat(path.c_str(), &s) == 0)
    {
        if(test == "-f" || test == "-d")
        {
            if(s.st_mode & S_IFDIR && test == "-d") 
            {
                cout << "(True)" << endl << "It is a directory" << endl;
                return true;
            }
            else if(s.st_mode & S_IFREG && test == "-f")
            {
                cout << "(True)" << endl << "It is a file" << endl;
                return true;
            }
            else
            {
                cout << "(False)" << endl;
                return false;
            }
        }
        else if(test == "-e") 
        {
            if((s.st_mode & S_IFDIR) || (s.st_mode & S_IFREG)){
                cout << "(True)" << endl;
                return true;
            }
            else
            {
                cout << "(False)" << endl;
                return false;
            }
        }
        else //Unrecognized operations
        {
            cout << "Unrecognized option!" << endl; 
            return false;
        }
    }
    cout << path << " not found." << endl;
    return false;
}

command::command(vector<string> cmd, string iFile, string oFile, bool appendflag, bool pipeFlag)
{
    input = cmd;
    inputFile = iFile;  //used for input redirection
    outputFile = oFile; //used for input redirection
    append = appendflag; //checks between appending or not for output redirection > and >>
    doPipe = pipeFlag;
    passedExecution = true;
    fdInputPipe = -1;
    arguments = new char*[input.size() + 1];
}

void command::parse()
{
    if(input.size() == 0)
    {
                                    //do nothing
    }
    else if(input.at(0) == "exit")  //checks to see if user typed exit
    { 
        exit(-1);                   //exits
    }
    else                            //otherwise, send commands to arguments char array
    { 
        for(unsigned i = 0; i < input.size(); i++)
        {
            arguments[i] = (char*)input.at(i).c_str();
        }
        arguments[input.size()] = NULL;
    }
}
void command::execCmd()
{
    int status;
    int fdin, fdout;
    int fdPipe[2];  //pipe takes two file descriptors
    this->parse();
    //cout << "doPipe: " << doPipe << "  fdInputPipe: "  << fdInputPipe << endl;
    if(doPipe)
    {
        pipe(fdPipe); //open the pipe
    }
    
    pid_t pid = fork();
    if (pid == 0) //CHILD PROCESS
    { 
        //test case
        if(input.size() != 0 && input.at(0) == "test")  //special case not using execvp
        {
            if(testCommand(arguments[1], arguments[2]))
            {
                exit(0);
            }
            else
            {
                exit(1);
            }
        }
        //redirection case and Pipe case
        
        if(fdInputPipe > 0)              //you can either take input from a pipe or a file.... THERE CAN BE ONLY ONE!
        {
            dup2(fdInputPipe, 0);
        }
        else if(inputFile != "") //if there is an input file
        {
            fdin = open(inputFile.c_str(), O_RDONLY); 
            dup2(fdin, 0); // replace standard input with input file
        }
        
        if(doPipe)
        {
            dup2(fdPipe[1], 1);  //redirect output of current command to pipe
            fdInputPipe = fdPipe[0]; //output of current command will be input to next command
            //cout << "fdPipe[0]: " << fdPipe[0] << "  fdPipe[1]: " << fdPipe[1] << endl;
        }
        else if(outputFile != "")
        {
            int flags;
            if(append)
            {
                flags = O_WRONLY | O_CREAT | O_APPEND; // >>
            }
            else
            {
                flags = O_WRONLY | O_TRUNC | O_CREAT; // >
            }
            fdout = open(outputFile.c_str(), flags, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            dup2(fdout, 1); // replace standard output with output file
        }
        if (execvp(arguments[0], arguments) == -1)
        {
            perror ("exec");
            exit(1); 
        }
    }
    if (pid > 0)//PARENT PROCESS
    { 
        if ( wait(&status) == -1) 
        {
            perror ("wait");
        }
        //cout << "doPipe: " << doPipe << "   fdPipe[0]: " << fdPipe[0] << "  fdPipe[1]: " << fdPipe[1] << endl;
        if(doPipe)
        {
            fdInputPipe = fdPipe[0]; //output of current command will be input to next command
            close(fdPipe[1]); //Must close
        }
        
        if(status)
        {
            passedExecution = false;
        }
        else
        {
            passedExecution = true;
        }
    }
    if (pid < 0)
    {
        cout << "fork() failed!\n";
        passedExecution = false;
    }
}

bool command::didCommand(){
    return this->passedExecution;
}

int command::didPipefd()
{
    return this->fdInputPipe;
}

void command::doSetPipefd(int fd)
{
    fdInputPipe = fd;
}
