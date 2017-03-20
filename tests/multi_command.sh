echo cool ; ls
ls -a ; ls -l
touch file ; echo world
[ -e main.cpp ] && echo hello world
test -e main.cpp || ls 
cat < main.cpp | tr a-z A-Z > cat.out
cat < main.cpp | tr A-Z a-z | tee cat.out | tr a-z A-Z > cat2.out
exit
