/*
Roll No:EE23B022
Name: Deepak Charan S
Date: 25.8.2023
Version:1.0
Description:To use the functions in the math library to generate a sequence of N random bits in the output file randbits.txt and also calculate the Hamming Distance between 2 bit streams
Inputs:In form of n (no. of random bits) and two input files containing bitstreams
Output: The calculated Hamming Distance and an output file containing the random N bit sequence*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>

int filein(int a){		//Function to write into file randbits.txt
 	FILE * fp = fopen("randbits.txt" , "w");
 	for(int i=0;i<a;i++){
 		fprintf(fp,"%d",rand()%2);
 		}
 	}


int main(int argc, char* argv[]){
	int c;
	int N;
	int seed;
	time_t t;
	int count=0;
	char a;
	char b;
	while ((c = getopt (argc, argv, "nsth:")) != -1){
		switch(c){
			case 'n':    //uses -n flag to collect value of N
				N=atoi(argv[optind]);
				
				break; 
			case 's': //uses -s flag to collect value of seed
				seed=atoi(argv[optind]);
				srand((unsigned) seed);
				break;
			case 't': //uses -t flag to use time value as seed
				srand((unsigned) time(&t));
				break;
			case 'h': //uses -h flag to calculate Hamming Distance
				printf("\n");  //was raising an error if `file pointer was declared just after case 'h' statement so added a dummy statement
				FILE* fp1 = fopen(argv[optind-1], "r"); 
				FILE* fp2 = fopen(argv[optind], "r"); 
				while(1){
        				a=fgetc(fp1);  //gets in 1 character from a at a time and checks it with b
					b=fgetc(fp2);
					if(a==EOF || b==EOF) //stops checking when a sequence has fully been iterated
						break;	
					else if(a!=b)
						count+=1; 
				}
		}
	}
	
 	
	filein(N);
	printf("%d \n",count);
	
	return 0;
}
			
				
				
