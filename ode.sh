#!/bin/bash

gcc ee23b022_ode.c -lm -o run
output_file="inputs.txt"
rm -f "$output_file"
for n in $(seq 0.01 0.01 0.5);
do ./run 0.175 2.967 0.1 $n >> "$output_file"
done
echo coolx

