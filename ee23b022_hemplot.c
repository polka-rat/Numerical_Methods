/*
Roll No:EE23B022
Name:Deepak Charan S
Date:14.11.23
Version:1.0
Description: Generating a Fibonacci plot
Output:  Output file titled 'rollnum_hemplot.txt'
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi M_PI
#define x0 0
#define y0 0
#define r0 10
#define range 400

int hem(int n){    //function to get hemachandra number
	if(n==1){
		return 0;
	}
	else if(n==2){
		return 1;
	}
	else{
		return hem(n-1)+hem(n-2);
	}
}

void hemplot(float x, float y, float theta,int a,int b,float r){  //function to generate the hemachandra plot
	FILE *fp1=fopen("ee23b022_hemplot.txt","w");
	int temp;
	float xa=x,ya=y;
	for(int i=0;i<=range;i++){
		fprintf(fp1,"%f %f\n",(x+xa)/2,(y+ya)/2);
		theta=(2*pi*a)/b;
		r+=(r0*a)/b;
		xa=x;
		ya=y;
		x=x0+r*cos(theta);   //new x value
		y=y0+r*sin(theta);   //new y value
		temp=a;
		a=a+b;
		b=temp;   //changing a and b values (following the hemachnadra pattern
	}
}
		
	

int main(int argc,char* argv[]){
	int x=x0,y=y0,r=r0;
	float theta;
	
	int a=2;
	int b=1;
	
	hemplot(x,y,theta,a,b,r);
	return 0;
}
