/*
Roll No:EE23B022
Name:Deepak Charan S
Date:19.9.23
Version:1.0
Description: Implementing the weighted union find algorithm using array manipulation
Input: An input file titled "file roads.txt"
Output: The time it took to run the program in milliseconds (rounded to the nearest integer) and the output (whether roads should be built or not) to be printed in file "ee23b022_quiz2_q4_output.txt"
Sources: https://www.techcrashcourse.com/2016/02/c-program-to-find-execute-time-of-program.html implementing clock function to get excution time.

https://www.youtube.com/watch?v=xc9s9wdaSdU to learn about weighted union find

 Few of my friends also gave me test cases to run and check
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int parent(int num,int arr[]){  //function to find the parent of an element
	if(arr[num]==-1){
		return num;
	}
	else{
		return parent(arr[num],arr);
	}
}

int main(int argc,char* argv[]){
	clock_t begin=clock(); //begins the clock 
	double exec_time=0.0;  //stores execution time
	FILE* fp1=fopen(argv[1],"r"); //reading requests from file
	FILE* fp2=fopen("ee23b022_quiz2_q4_output.txt","w"); //printing output in file
	int planet,req;
	fscanf(fp1,"%d %d",&planet,&req); //getting value of number of planets and requests
	int root[planet];  //making a root array which stores parents of each item 
	int weight[planet]; //array to store the weight of each tree (only gets stored in the parent index)
	for(int i=0;i<planet;i++){
		root[i]=-1; //initializing all value of root as -1
		weight[i]=0; //initializing weight of all index as 0
	}
	int par1,par2,plan1,plan2;
	for(int j=0;j<req;j++){
		fscanf(fp1,"%d %d",&plan1,&plan2); //getting value of the 2 planets we must build a road in between (if not connected)
		par1=parent(plan1,root); //getting parent of planet 1
		par2=parent(plan2,root); //getting parent of planet 2
		if(par1!=par2){ //checking if parents of both the planets are same (if same, that means they are connected
			if(weight[par1]<weight[par2]){ //comparing weights of both parents
				weight[par2]+=weight[par1]+1; //adding the weights of planet 1's parent to planet 2(as it is now the representative of the second set too
				root[par1]=par2;  //connecting the 2 sets (by making the parent of the smaller set as the parent of the larger set 
				
			}
			else{ //vice versa
				weight[par1]+=weight[par2]+1;
				root[par2]=par1;
			}
			fprintf(fp2,"%d",1);
		}
		else{   //planets are connected (no need to build roads)
			fprintf(fp2,"%d",0);
		}
	}
	fclose(fp1);
	clock_t end=clock();  //ending clock
	exec_time+=(double)(end - begin)/CLOCKS_PER_SEC;  //calculating execution time
	int rounded_exec_time=round(exec_time*1000); //rounding the execution time to the nearest integer
	fprintf(fp2," \n%d ms",rounded_exec_time);
	fclose(fp2);
	return 0;
}
			
				
