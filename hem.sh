#!/bin/bash

gcc ee23b022_hem.c -o run

rm -f "ee23b022_hem.txt"

for i in {2..5}
do
	a=$(./run $i)
	b=$(./run $((i + 1)))
	result=$(echo "scale=6; $b / $a" | bc)
	echo $i	$a $result >> ee23b022_hem.txt
done

gnuplot ee23b022_hem.gp

