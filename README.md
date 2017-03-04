# rshell

Writing a Basic Command Shell - Assignment 3
=============================================

This program builds on our previous shell program. It contains all of the previous functionally
with new functionality added. First, we added "test / []" which allows the user to test a certain
file path. Test also includes "-e", "-d", "-f". "-e" returns true if the path leads a valid file 
or directory. "-d" returns true if the path exists and it leads to a directory. "-f" returns true
if the path exists and leads to a file. We also added support for parenthesis.

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
    Xf@ericchang123-cs100assignments-4415658$ ( echo hi ) && ls
    Xf@ericchang123-cs100assignments-4415658$ ( echo hi && echo hello ) && ls
    Xf@ericchang123-cs100assignments-4415658$ [ - e main.cpp ] || ls
    Xf@ericchang123-cs100assignments-4415658$ test - e main.cpp && ls && echo hi

Bugs: 
=========

Due to nature of c strings, cant handle over parenthesized notation.



