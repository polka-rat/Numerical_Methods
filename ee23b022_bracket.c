/*
Roll No:EE23B022
Name: Deepak Charan S
Date: 1.9.23

Version: 1.1 (solving using recursion led to many bugs so decided to go with while loops)

Desciption: Find the real roots of   f(x) = -25 + 82x - 90 x^2 + 44 x^3 - 8 x^4 + 0.7 x^5 using:
i)bisection with epsilon =10% and xl = 0.5, xu = 1.0 and..
ii)Repeat with the false position method with epsilon = 0.2%

Input:the method to solve (1 for bisection method; 2(or any other number except 1) for false position method

Output: the value of calculated root
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float poly(float x){                               //Function for calculating the value of the polynomial using a given x
	return 0.7*pow(x,5) - 8*pow(x,4) + 44*pow(x,3) - 90*pow(x,2) + 82*pow(x,1)-25;
}

int main(int argc, char* argv[]){
	float xl=0.5;                              //lower limit
	float xu=1.0;				    //upper limit
	float xm=0.75;				    //temporary mean value
	float xmold=20;			    //stores old mean value (for epsilon calculation) 
	int i=atoi(argv[1]);
	
	if(i==1){
		while(1){
			xm=(xu+xl)/2;
			if((fabs(xm-xmold)*100/xm)<10){  //epsilon value
				printf("%f \n",xm);
				break;
			}
			else{
				xmold=xm;
				if(poly(xl)*poly(xm)<0){
					xu=xm;           //root is between xl and xm
				}
				else{
					xl=xm;		 //root is between xm and xu
				}
			}
		}
	}
	else{
		while(1){
			xm=xu-(poly(xu)*(xl-xu))/(poly(xl)-poly(xu));  //calculation of the value of x intercept of line joining (xu,f(xu)) and (xl,f(xl))
			if((fabs(xm-xmold)*100/xm)<0.2){		//epsilon calculation
				printf("%f \n",xm);
				break;
			}
			else{
				xmold=xm;
				if(poly(xl)*poly(xm)<0){
					xu=xm;				//root is between xl and xm
				}
				else{
					xl=xm;				//root is between xu and xm
				}
			}
		}
	}
	
	return 0;
}
				
		
	
