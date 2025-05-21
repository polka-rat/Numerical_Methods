#!/bin/bash

gcc ee23b022_hem.c -o run

output_file1="first_num.txt"
rm -f "$output_file1"
output_file2="second_num.txt"
rm -f "$output_file2"
for i in {1..5}
do
	./run $i >> "$output_file1"
	./run $(expr $i+1) >> "$output_file2"
	echo $first_num
	echo $second_num
done
echo sexxx
	
	
