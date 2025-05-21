#!/bin/bash

rm -f "readings.txt"
input="ip.txt"
while IFS= read -r line
do
  ping $line  -i 0.002 -c 100 >pingstmp.txt
  echo -n "$line" " " >> readings.txt
  awk '{print $8}' pingstmp.txt >collection.txt
  awk -F '=' 'BEGIN{x=0}{x+=$2}END{print x/NR}' collection.txt >> readings.txt
done < "$input"



