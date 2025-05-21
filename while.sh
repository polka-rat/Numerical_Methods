#!/bin/bash

myvar=1

while [ $myvar -le 10 ]
do
expr $myvar + 1 
myvar=$(($myvar+1))
done
echo sexxxxx
