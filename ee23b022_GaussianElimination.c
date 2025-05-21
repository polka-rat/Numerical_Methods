/*
Roll no: EE23B022
Name: Deepak Charan S
Input:
N-> an input file and an integer n, denoting the number of rows
Output: N lines of floats giving the various values of x
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void pivot(double **a,int k, int n, double *b, double *s){ //pivots the columns to make sure no division by zero happens
	double big = fabs(a[k][k]);
	int big_position = k;
	double dummy;
	for(int i=k+1;i<n;i++){
		if(fabs(a[k][i]) > big){ //finds the largest value in the row
			big = fabs(a[k][i]);
			big_position = i;
		}
		
	}
	
	if(big_position != k){ //swaps the column with the largest value with k.
		for(int j=0;j<n;j++){
			dummy = a[j][k];
			a[j][k] = a[j][big_position];
			a[j][big_position] = dummy;
		}
		dummy = b[k];
		b[k] = b[big_position];
		b[big_position] = dummy;
		
		dummy = s[k];
		s[k] = s[big_position];
		s[big_position] = dummy;
	}
}

void eliminate(double **a, int N,double *b, double tol, int *err){
	double *s = malloc(sizeof(double)*N);
	
	for(int i=0;i<N;i++){ //finds the largest coeffecient in a column
		double l = a[0][i];
		for(int j=1;j<N;j++){
			if(a[j][i] > l) l = a[j][i];
		}
		s[i] = l;
	}
	
	for(int k=0;k<N-1;k++){ //iterates through N-1 rows
		pivot(a,k,N,b,s); //pivots to avoid division by zero
		if(fabs(a[k][k]/s[k]) < tol){ //checks if the coeff ratio is too small leading to sensitive systems
			*err =-1;
			break;
			
		}
		for(int i=k+1;i<N;i++){ //iterating through columns
			double factor = a[k][i]/(a[k][k]);
			for(int j=k;j<N;j++){ //iterating throught rows
				a[j][i] -= factor*a[j][k];
			}
			b[i] -= factor*b[k];
		}
	}
	
}

void back_sub(double **a, int n, double *b, double *x){
	
	x[n-1] = b[n-1]/a[n-1][n-1];
	
	for(int i=n-2;i>-1;i--){ //iterate through columns backwards
		double sum = b[i];
		for(int j=i+1;j<n;j++){ //iterate through rows
			sum-=a[j][i]*x[j]; 
		}
		x[i] = sum/a[i][i];//find x[i]
	}
}


int main(int argc, char *argv[]){
	int N = atoi(argv[2]);	
	double **a = malloc(sizeof(int *)*N);
	for(int i=0;i<N;i++)a[i] = malloc(sizeof(int)*N);
	double *b = malloc(sizeof(int)*N);
	double *x = malloc(sizeof(int)*N);
	FILE*fp;
	fp = fopen(argv[1], "r");
	
	for(int i =0;i<N;i++){ //reading file
		for(int j=0;j<N;j++) fscanf(fp, "%lf ", &a[j][i]);	
		fscanf(fp, "%lf\n", &b[i]);
	}
	
	int err=0;
	double tol = 0.01;
	eliminate(a, N, b, tol, &err); //eliminating coeffecients
	back_sub(a, N, b, x);
	
	if(err == -1) return 0;//checking if system is too sensitive
	for(int i=0;i<N;i++){
		printf("%lf\n", x[i]);
	}
	
						
}
