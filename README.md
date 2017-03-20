# rshell

Writing a Basic Command Shell - Assignment 3
=============================================

This program builds on our previous shell program. Shell class outputs a prompt that 
includes the user's username and hostname. The user is able to enter as many commands 
and prompts as he/she desires. We read in the prompt by using a string stream and 
parse by checking whether or not the "word" is a connector or a command. Then we 
connect each connector with a child command*. This is why we have a head connector 
that always executes the following command. We added "test / []" which allows the user 
to test a certain file path. Test also includes "-e", "-d", "-f". "-e" returns true 
if the path leads a valid file or directory. "-d" returns true if the path exists 
and it leads to a directory. "-f" returns true if the path exists and leads to a file. 
We added support for parenthesis. We have now added support for redirection. 
Input, output and pipe.

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
    Xf@ericchang123-cs100assignments-4415658$ ls && ps
    Xf@ericchang123-cs100assignments-4415658$ ls || ps
    Xf@ericchang123-cs100assignments-4415658$ ls | tr a-z A-Z
    Xf@ericchang123-cs100assignments-4415658$ cat main.cpp > cat.out
    Xf@ericchang123-cs100assignments-4415658$ cat main.cpp >> cat.out

Bugs: 
=========

-Due to nature of c strings, cant handle over parenthesized notation.



