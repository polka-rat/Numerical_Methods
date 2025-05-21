#!/bin/bash

gcc ee23b022_ode.c -lm -o run
for i in {1..3}
do
./run 0.0175 3.1415926 0.2 0.1
done
