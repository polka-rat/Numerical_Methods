/*
Roll No:Deepak Charan S
Date: 18.8.2023
Version:1.0
Description:Code to compute the value of sin(x) using series expansion and calculating the error from the actual value of sin(x)
Inputs:In form of n (no. of terms) and x (the value inside sin)
Output: comma-separatede values of calculated value of sin(x) and error*/
  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float factorial(int m){          //function for getting a factorial
	float fact=1.0;
	for(int i=1;i<=m;i++){
		fact*=i;
	}
	return fact;
	}
float term(float x,int n){		// function for getting each term of series
	return pow(x,(2*n-1))/factorial(2*n-1);
	}

int main(int argc, char* argv[]){
	int i=atoi(argv[1]);
	float j=atof(argv[2]);
	float sum=0.0;
	for (int p=1;p<=i;p++){          //Computing the summation
		sum+=pow(-1,p-1)*term(j,p);   
		
	}
	float error=sin(j)-sum;          //error value
	printf("%.3f,%.3f",sum,error);
	return 0;
}
