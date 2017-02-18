#include <iostream>
using namespace std;
/*this is the Command BASE CLASS and it has 2 SUBCLASSES
"BuiltIn" and "Executable" The BuiltIn has another subclass 
called "Exit" which is handles the Built In Command Exit */

class command{
    
};

class BuiltIn : public command{
  public:
    BuiltIn();
};

class Executable : public command{
  public:
    Executable();
};