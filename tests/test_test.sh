#!/bin/sh
test -e tests && echo this exists
test -d tests && echo this is a directory
test -f tests && echo this is not a file
[ -f tests ] && echo this is not a file
exit
