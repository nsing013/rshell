#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// Executable
//Fork/Execv/Wait


// What we want to do is type in commands and put them in this array so that 
// our fork process will read our command from the array and run it in the terminal
    
    //Fork/execv/wait process
    char p1[] = "/bin/ls"; //temporarily set the elements in the array
    char p2[] = "-l";      
    
    char* argv[10]; //array of commands IMPORTANT this is where we put in our commands
    argv[0] = p1;          //temporarily set the elements in the array
    argv[1] = p2;          
    argv[2] = NULL;

    pid_t pid = fork(); //forking
    int status; //sets the status of the child process

    if (pid == 0) // child process
    {
        cout << "child" << endl;
        execv(argv[0], argv);
    }
    else if (pid > 0) // parent process
    {
        cout << "parent" << endl;
        pid_t tpid = wait(&status);
    }
    else // fork failed
    {
        cout << "fork() failed!\n";
        return 1;
    }
    return 0;


