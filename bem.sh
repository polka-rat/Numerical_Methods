#!/bin/bash

#Roll No:EE23B022
#Name:Deepak Charan S
#Date: 14.11.2023
#Bash script to execute ee23b022_hem.c for a certain number of times to calculate ratios of consecutive hemachandra numbers

gcc ee23b022_hem.c -o run

rm -f "ee23b022_hem.txt"

for i in {2..10}       #for loop
do
	a=$(./run $i)   #first hem number
	b=$(./run $((i + 1)))  #second hem number
	result=$(echo "scale=6; $b / $a" | bc)
	echo $i	$a $result >> ee23b022_hem.txt
done

gnuplot ee23b022_hem.gp   #running a gnuplot script to plot the grpah of i th value and the i th ratio
