#!/bin/bash

for line1 in $(cat input_files.txt)
do
	outcount=1
	incount=1
	for line2 in $(cat checking_files.txt)
	do
		if [ $incount -ne $outcount ]
		then
			incount=$(($incount + 1))
			continue
		else		
		gcc ee23b022_quiz2_q3.c -lm -o run
		./run $line1 
		grep -z -v ms ee23b022_quiz2_q3_output.txt > stu_file.txt
		grep -z -v ms $line2 > check_file.txt

		if cmp stu_file.txt check_file.txt; then
			echo "Good job bro!"
		else
			echo "Gaand me danda de"
		fi
		fi
	outcount=$(($outcount + 1))
	done
done
