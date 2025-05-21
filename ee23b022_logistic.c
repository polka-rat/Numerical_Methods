/*
Roll No:ee23b022
Name: Deepak Charan S
Date: 8.9.23
Version:1.3
Description: To create a logistic map (A demographic model written as x[n+1] = r x[n] (1-x[n])) and iterate the equation for the parameter range r = [0,4] with x between 0 and 1.
Save the data as two columns (r,x), plot it to generate the bifurcation plot
Input: no. of iterations (as first term), increments (as second term), tolerance (as third term)
Output: a jpeg file of the graph
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 



int main(int argc, char* argv[]){
	FILE* fp=fopen("outfile.txt","w");          
	float r,x=0.04,y,xold,temp,inc,eps;  //intializing variables
	xold=0.5;
	int iter=atoi(argv[1]);
	inc=atof(argv[2]);
	eps=atof(argv[3]);
	int count=0;
	r=1;
	
	
	
	for(float j=0;j<=1;j=j+inc)//as value of x is always 0 for all r from 0to 1 and graph gets awry when r is less than 1
    {
        fprintf(fp,"%f %f\n",j,0.000000);

    }
	

	while(r<4){    
		
		while(count<iter&&abs(100*((x*r*(1-x)-x)/x))){  //tolerance condition
			count++;
			temp=x;
			x=r*xold*(1-xold);
			xold=temp;
			
			

				fprintf(fp,"%f \t %f \n",r,x);  //writing into file
			

		}
		r=r+inc;
		count=0;
	}
	
	return 0;
}
