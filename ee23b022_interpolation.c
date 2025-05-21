#include <stdio.h>
#include <stdlib.h>

float lag(float x[],float y[], int n,float xx){
	float sum=0;
	float product;
	for(int i=0;i<=n;i++){
		product=y[i];
		for(int j=0;j<=n;j++){
			if(i!=j){
				product*=(xx-x[j])/(x[i]-x[j]);
			}
		}
		sum+=product;
	}
	float lgr=sum;
	return lgr;
}

float poly(float x){
	float val=1/(1+25*x*x);
	return val;
}	

float newt(float x[],float y[],int n, float xo){
	float fdd[n][n];
	for(int i=0;i<=n;i++){
		fdd[i][0]=y[i];
	}
	for(int j=1;j<=n;j++){
		for(int i=0;i<=n-j;i++){
			fdd[i][j]=(fdd[i+1][j-1]-fdd[i][j-1])/(x[i+j]-x[i]);
		}
	}
	float xterm=1;
	float yint=fdd[0][0];
	float yint2;
	
	for (int order = 1; order <= n; order++) {
        xterm = xterm * (xo - x[order - 1]);
        yint2 = yint + (fdd[0][order] * xterm);
        yint = yint2;
    }
    
    // Print the interpolated value
    printf("%f", yint);
}
	

int main(int argc, char* argv[]){
	int poly_order=atoi(argv[1]);
	float xstart=atof(argv[2]);
	float xend=atof(argv[3]);
	float x0=atof(argv[4]);
	
	float diff = (xend - xstart)/(poly_order);
	
	float x[poly_order+1];
	float y[poly_order+1];
	float new_x[poly_order+1];
	float new_y[poly_order+1];
	
	for(int i=0;i<=poly_order;i++){
		x[i] = xstart + i * diff;
		y[i]=poly(x[i]);
	}
	for (int i = 0; i <= poly_order; i++) {
        new_x[i] = (x[1] - x[0]) / 10 + x[i];
    	}
    	for (int i = 0; i <= poly_order; i++) {
        new_y[i] = lag(x,y,poly_order,new_x[i]);
    	}
	
	newt(new_x,new_y,poly_order,x0);
	return 0;
}
	
