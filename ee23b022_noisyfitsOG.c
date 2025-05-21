/*
Roll No:EE23B022

Name:Deepak Charan S

Date:27.10.23

Version:1.0

Description: 1.Start with a baseline noisy series of length N with zero mean and standard deviation sigma_n (you can reuse the code from a previous assignment on the Box-Muller transform that converts uniform random distribution to a normal distribution)
2.Add to it a Lorentzian curve of the form f(x) = 1/(1+25 x^2), with x ranging from -2 to 2.
3.Fit the data to a Gaussian of the from g(x) = A * exp(-x^2/(2*sigma_g^2))
4.Plot the goodness of fit R^2 versus sigma_n. Label both axis of the plot.

Input: N sigma_n 
Output: sigma_n A sigma_g R^2

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define pi M_PI

double box_cos(double a,double b){  //Generating term from Box Muller Transformation
	double x;
	x=sqrt((-2)*log(a))*cos(2*pi*b);
	return x;
}

double lorentz(double x){   //lorentz curve
	return 1/(1+25*pow(x,2));
}

double gauss(double A,double sigma_g,float x){  //gaussian curve
	return A*exp(-x*x/(2*sigma_g*sigma_g)); 
}

float r_squared(float Y[], float y[], int n)  //function to get r^2
{
    float sum_y = 0.0;
    float sum_y_squared = 0.0;
    float sum_residuals_squared = 0.0;
    float mean_y, y_pred;

    for (int i = 0; i < n; i++)
    {
        sum_y += y[i];
        sum_y_squared += y[i] * y[i];
    }

    mean_y = sum_y / n;

    for (int i = 0; i < n; i++)
    {
        y_pred = Y[i];
        sum_residuals_squared += (y[i] - y_pred) * (y[i] - y_pred);
    }

    float r_squared = 1.0 - (sum_residuals_squared / (sum_y_squared - n * mean_y * mean_y));
    return r_squared;
}

int main(int argc,char* argv[]){
	int N=atoi(argv[1]);
	float sig=atof(argv[2]);
	srand(time(NULL));
	FILE* fp1=fopen("BaselessNoise.txt","w");
	double max=RAND_MAX;
	float inc=(4.0/(N-1));
	
	float *Y=(float*)malloc(100000*sizeof(float));
	float *y=(float*)malloc(100000*sizeof(float));
	
	int count=0;
	
	for(float i=-2;i<=2;i+=inc){
		double u1=rand()/max;
		double u2=rand()/max;
		double noise=box_cos(u1,u2)*sig/6;
		double point=lorentz(i)+noise;
		fprintf(fp1,"%lf %lf\n",i,point);   //plotting points of lorentzian curve
		Y[count]=point;
		count++;
	}
	
	count =0;
        fclose(fp1);
	//code to write gnuplot commands in c-file
	
	FILE *gnuplotPipe;
    	gnuplotPipe = popen("gnuplot", "w"); // Start Gnuplot

        // Open a file for text output
    	FILE *outputFile = fopen("ee23b022_gnuplot_output.txt", "w");

        // Redirect the Gnuplot output to a file
        fprintf(gnuplotPipe, "set fit quiet\n");
	fprintf(gnuplotPipe, "set print 'ee23b022_gnuplot_output.txt'\n");

        // Gnuplot commands for plotting or other operations
        fprintf(gnuplotPipe, "f(x)=A * exp(-x*x/(2*sigma_g*sigma_g))\n");   
        fprintf(gnuplotPipe, "fit f(x) 'BaselessNoise.txt' via A, sigma_g\n");
        fprintf(gnuplotPipe, "print A\n");
        fprintf(gnuplotPipe, "print sigma_g\n");
        // Close the Gnuplot pipe
        pclose(gnuplotPipe);

        fclose(outputFile);
    	double A,sigma_g;
        FILE* fp2=fopen("ee23b022_gnuplot_output.txt","r");
        fscanf(fp2, "%lf",&A);  //getting A and sigma_g values from the fitted gaussian curve
        fscanf(fp2, "%lf",&sigma_g);
        
        for(float i=-2;i<=2;i+=inc){
		y[count]=gauss(A,sigma_g,i);
		count++;
	}
	float r_square=fabs(r_squared(Y,y,count));
	printf("%f %lf %lf %f \n",sig,A,sigma_g,r_square);
	return 0;
}
	
	
