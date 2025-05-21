/*
Roll No:EE23B022
Name:Deepak Charan S
Date:21.9.23
Version:1.1
Description: Implementing the weighted union find algorithm using structs
Input: An input file entered in command line
Output: The time it took to run the program in milliseconds (rounded to the nearest integer) and the output (whether roads should be built or not) to be printed in file "ee23b022_quiz2_q3_output.txt"
Sources: https://www.techcrashcourse.com/2016/02/c-program-to-find-execute-time-of-program.html implementing clock function to get excution time.
https://www.youtube.com/watch?v=xc9s9wdaSdU to learn about weighted union find.

 N. Deenabandhan (EE23B021) gave me the syntaxes to use an array which stores pointers to all planets.

Few of my friends also gave me test cases to run and check
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct planet{  //making a struct planet
	int plan_num;   //storing the number of the planet
	int weight;     //storing the weight of the planet (useful if it is the parnet of another planet)
	struct planet* parent;  //stores the pointer of the element's parent
	
}planet;

void create(int plan_num,int weight,planet arr[]) {   //creating a new element and storing its pointer in an array
    arr[plan_num].plan_num=plan_num;  //storing the planet number
    arr[plan_num].parent=&arr[plan_num]; //initialising the address of the parent element as itself
    arr[plan_num].weight=0;  //intialising the value of weight as 0 (as no planet would act as the representative at the very start)
    
}

int find_parent(int num,planet arr[]){ //function the find the representative element(planet)
	if(arr[num].parent==&arr[num]){  //planet is the representative
		return num;
	}
	else{  //planet has a parent
		return find_parent(arr[num].parent->plan_num,arr); //running a recursion to get the parent of the parent (if it exists)
	}
}

int main(int argc, char* argv[]){
	clock_t begin=clock(); //begins the clock 
	double exec_time=0.0;  //stores execution time
	FILE* fp1=fopen(argv[1],"r"); //reading requests from file
	FILE* fp2=fopen("ee23b022_quiz2_q3_output.txt","w");  //write into this file
	
	int plan,req;
	fscanf(fp1,"%d %d",&plan,&req); //getting value of number of planets and requests
	
	planet *arr=(planet*)malloc(plan*sizeof(planet));  //initialising the array of pointers to the planets

	
	for(int i=0;i<plan;i++){  //creating structs for each planet
		create(i,0,arr);
	}
	
	int plan1,plan2,plan1_par,plan2_par;
	for(int j=0;j<req;j++){
		fscanf(fp1,"%d %d",&plan1,&plan2); //getting value of the 2 planets we must build a road in between (if not connected)
		plan1_par=find_parent(plan1,arr);  //getting representative of planet 1
		plan2_par=find_parent(plan2,arr);	//getting representative of planet 2
		if(plan1_par!=plan2_par){  //planets are not connected
			fprintf(fp2,"%d",1);
			if(arr[plan1_par].weight<arr[plan2_par].weight){ //comparing weights of both representatives
				arr[plan2_par].weight+=arr[plan1_par].weight+1; 	//adding the weights of planet 1's parent to planet 2(as it is now the representative of the second set too				
				arr[plan1_par].parent=&arr[plan2_par];  //representative of planet 1 is now representative of planet 2
				}
			else{  //vice versa
				arr[plan1_par].weight+=arr[plan2_par].weight+1;   
					arr[plan2_par].parent=&arr[plan1_par];
			}
		} 
		else{  //planets are connected (no need to build roads)
			fprintf(fp2,"%d",0);
		}
	}
	fclose(fp1);
	clock_t end=clock(); //ends the clock
	exec_time+=(double)(end - begin)/CLOCKS_PER_SEC; //calculating execution time
	int rounded_exec_time=round(exec_time*1000);  //rounding the execution time to the nearest integer
	fprintf(fp2," \n%d ms",rounded_exec_time);
	fclose(fp2);
	free(arr);
	return 0;
}
