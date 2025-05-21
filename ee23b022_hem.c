/*

Roll No:EE23B022
Name:Deepak Charan S
Date:14.11.23
Version:1.0
Description: Generate the mth Hemachandra number
Input: An integer n
Output:  The value of the mth hemachandra number
*/
#include <stdio.h>
#include <stdlib.h>

int hem(int n){   //function to calculate hemachandra number
	if(n==1){
		return 0;  //first hemachandra number
	}
	else if(n==2){
		return 1;  //second hemachandra number
	}
	else{
		return hem(n-1)+hem(n-2);  //running a recursion
	}
}

int main(int argc,char* argv[]){
	int m=atoi(argv[1]);
	printf("%d\n",hem(m));	
	return 0;
}
