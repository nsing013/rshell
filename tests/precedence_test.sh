#!/bin/sh
(echo a && echo b) || (echo c && echo d)
((ls && ls) && ls) && ls
( [-e main.cpp] && ls) && ls 
(echo a || echo b) && (ls -l || ls)
exit
