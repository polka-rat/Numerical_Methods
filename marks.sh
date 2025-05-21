#!/bin/bash

gcc ee23b022_quiz2_q3.c -lm -o run
./run roads1e5_1e5.txt
grep -v ms ee23b022_quiz2_q3_output.txt > temp1.txt
sed 's/\n$//' temp1.txt > stu_file.txt
grep -v ms roads1e5_1e5_output.txt > temp2.txt
sed 's/\n$//' temp2.txt > check_file.txt

if cmp ee23b022_quiz2_q3_output.txt roads1e5_1e5_output.txt; then
	echo "Good job bro!"
else
	echo "Gaand me danda de"
fi
