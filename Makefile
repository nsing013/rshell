
CPP_FILES = src/main.cpp src/shell.cpp src/connector.cpp src/command.cpp

H_FILES = src/shell.h src/connector.h src/command.h

all : $(CPP_FILES) $(H_FILES)
	[ -d bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -o bin/rshell $(CPP_FILES)
	
rshell : $(CPP_FILES) $(H_FILES)
	[ -d bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -o bin/rshell $(CPP_FILES)
