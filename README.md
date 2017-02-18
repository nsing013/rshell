# rshell


Writing a Basic Command Shell - Assignment 2
=============================================

The way our program works, is the shell class outputs a prompt that includes the user's username and hostname. The user is 
able to enter as many commands and prompts as he/she desires. We read in
the prompt by using a string stream and parse by checking whether or not the 
"word" is a connector or a command. Then we connect each connector with a child
command*. This is why we have a head connector that always executes the following
command. 

Files:
=======

* shell.cpp
* shell.h
* connector.cpp
* connector.h
* command.cpp 
* command.h
* main.cpp

How to build:
=============

    $ make
    
How to run:
===========

    $ ./rshell
    
Examples: 
=========

    $ ./rshell
    Xf@ericchang123-cs100assignments-4415658$ ls
    Xf@ericchang123-cs100assignments-4415658$ ps
    Xf@ericchang123-cs100assignments-4415658$ ls ; ps
    Xf@ericchang123-cs100assignments-4415658$ ls && ps
    Xf@ericchang123-cs100assignments-4415658$ ls || ps

Known Bugs: 
===========

- When you type the commands without spaces, it wont parse and will give you and error "No such file or directory". Must have spaces.
- unknown commands (ie. xx) do not return any values. If there is an unknown command, the program should move on to the next command if there is one, however the code is not handling it.

