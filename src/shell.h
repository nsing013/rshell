#include <iostream>
using namespace std;

/*This class is the shell class. IT HAS NO CHILDREN!!! 
BUT, it outputs a prompt, takes a command, and outputs a 
prompt again. We use a linked list to store the connectors 
entered by the user */

//classes go here
class shell{
  public:
    shell();
    void run();
  private:
    char userName[128];
    char hostName[128];
};