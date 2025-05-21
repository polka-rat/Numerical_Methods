#!/bin/bash
output_file="ee23b112_hem.txt"
rm -f $output_file

gcc ee23b112_hem.c -o hem

for n in {2..30}
do
    nth_term=$(./hem $n)
    nplus1th_term=$(./hem $((n+1)))
    ratio=$(echo "scale=5; $nplus1th_term / $nth_term" | bc)

    echo -e "$n\t$nth_term\t$ratio" >> ee23b112_hem.txt
done

gnuplot ee23b112_hem.gp


#gnuplot -c ee23b112_hem.gp

echo "done"

