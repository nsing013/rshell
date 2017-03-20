#!/bin/sh
ls > lsfile
cat < lsfile | tr A-Z a-z | tee lstest1.txt | tr a-z A-Z > lstest2.txt
ls | tr a-z A-Z
ls | tee ls.txt
ls -l >> extendedls.txt
du | sort -nr
cat < extendedls.txt
echo this is a test of output redirection showing overwriting > extendedls.txt
cat < extendedls.txt
echo this is a test of output redirection showing appending >> extendedls.txt
cat < extendedls.txt
ls -l > unsorted.txt
cat < unsorted.txt
echo unsorted file
sort < unsorted.txt > sorted.txt
cat < sorted.txt
echo sorted file
exit
