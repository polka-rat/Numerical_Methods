/*
Roll No:EE23B022
Name: Deepak Charan S
Date: 30.9.2023
Version: 1.1 (first code got too messy so i had to reconstruct old code with better variable naming)
Description: 1.Generating normal distributions for noise eps_T, eps_a, n (Getting eps_T,eps_a using Box Muller Transformation)
	     2.Generating a time series of Lorentzians  s(t) separated by T with width proportional to a and adding noise to it	
	     3.Identifying the locations of the peaks and estimating T and a
Input:in form of M,T,a,type of graph (type l for Lorentzian;g for Gaussian) in the respective order
Output: avg(T),avg(a),stdev(T),stdev(a) in the respective order

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define pi M_PI   
#define inc_coeff 0.1



typedef struct peak{  //defining a struct for each peak
	double loc;   
	double amp;
	double width; 
}peak;

peak* create(double loc,double amp,double width){
	peak* new = (peak*)malloc(sizeof(peak));
	new->loc = loc;
	new->amp = amp;
	new->width = width;
	return new;
}

double box_cos(double a,double b){  //Generating first term of Box Muller Transformation
	double x;
	x=sqrt((-2)*log(a))*cos(2*pi*b);
	return x*inc_coeff;
}

double box_sin(double a,double b){ //Generating second term of Box Muller Transformation
	double y;
	y=sqrt((-2)*log(a))*sin(2*pi*b);
	return y*inc_coeff;
}

double window(double* array,int n){  //Function to denoise the curve
	double wind_sum=0.0;
	for(int j=n;j<n+10;j++){
		wind_sum+=array[j];
	}
	return wind_sum/10;
}

int main(int argc, char* argv[]){
	int M=atoi(argv[1]); 
	double T=atof(argv[2]);
	double b=atof(argv[3]);
		
	srand(time(NULL));
	double max=(long double)RAND_MAX;  //Getting max value possible from a random number generation
	
	int count=0; //to get number of points in graph
	
	double *points_arr = (double*)malloc(10000000 * sizeof(double)); //array to store the functional value
	double *time_arr = (double*)malloc(10000000 * sizeof(double)); //array to store the time
	double *noiseless=(double*)malloc(10000000 * sizeof(double)); //array to store the noiseless functional value
	
	double u1,u2,a,point;
	double exp_pow;
	
	double *a_arr = (double*)malloc(10000000 * sizeof(double));
	int a_count=0;
		
	if(argv[4][0]=='l'){          //lorentzian curve
		for(int m=1;m<=M;m++){
			for(float time=((T*m)-(T/2));time<((T*m)+(T/2));time+=0.1){
				u1=rand()/max;
				u2=rand()/max;
				a=b;
				a+=a*box_cos(u1,u2);			 //adding noise to a
				point=(pow(a,2))/(pow(time-(m*T+box_sin(u1,u2)),2)+pow(a,2))+0.1*box_cos(u1,u2); //adding noise to T and overall functional value	
				points_arr[count]=point;
				time_arr[count]=time;
				count++;
			}
		}
	}
	else{          //gaussian curve
		
		FILE* fp=fopen("Gaussian.txt","w");
		for(int m=1;m<=M;m++){
			for(float time=((T*m)-(T/2));time<((T*m)+(T/2));time+=0.1){
				u1=rand()/max;
				u2=rand()/max;
				a=b;
				a+=box_cos(u1,u2);
				a_arr[a_count]=a;
				a_count+=1;
				exp_pow=(-1)*((pow(time-(m*T+box_sin(u1,u2)),2))/2*pow(a,2));		 //adding noise to a
				point=1*exp(exp_pow)+inc_coeff*box_cos(u1,u2); //adding noise to T and overall functional value	
				points_arr[count]=point;
				time_arr[count]=time;
				count++;
				fprintf(fp,"%lf %lf \n",time,point);
			}
		}
		fclose(fp);		
	}
	for(int i=0;i<count;i++){
		noiseless[i]=window(points_arr,i);  //genrating noiseless curve
	}
	
	double max_values[M],sums[M],sq_sums[M],peak_points[M],peak_times[M],width_arr[M];
	double first,second,width=0,width_sq_sum=0;
	double time_sum=0,time_sq_sum=0,time_diff;
	double a_sum=0,a_sq_sum=0,a_val;
	
	
	for(int j=0;j<M;j++){
		max_values[j]=0;
		first=-1.0;
		for(int k=j*count/M;k<(j+1)*count/M;k++){
			if(noiseless[k]>max_values[j]){
				max_values[j]=noiseless[k];  //to generate the max value of each hill
			}
		}
		for(int k=j*count/M;k<(j+1)*count/M;k++){
			if(noiseless[k]<=max_values[j]/2 && first!=-1.0 ){  //Graphically speaking, drawing a line y=amplitude/2 and taking the average of the intersection points
				second=time_arr[k];
				peak_times[j]=(first+second)/2;
				if(argv[4][0]=='l'){
					a_val=((second-first)/(2*sqrt(log(4))));
					a_sum+=a_val;
					a_sq_sum+=a_val*a_val;
					width+=((second-first)/2);   //calculating value of a
					width_arr[j]=((second-first)/2);
					width_sq_sum+=pow(((second-first)/2),2);
				}
				else{
					width+=(a_arr[j]);   //calculating value of a
					width_arr[j]=a_arr[j];
					width_sq_sum+=pow(width_arr[j],2);				
				} 
				break;
			}
			else if(noiseless[k]>=max_values[j]/2 && first==-1.0){
				first=time_arr[k];
			}				
		}
		create(peak_times[j],max_values[j],width_arr[j]);
		
	}
	
	for(int m=0;m<M-1;m++){
		time_diff=(peak_times[m+1]-peak_times[m]);  //getting the time difference between two peaks 
		time_sum+=time_diff;
		time_sq_sum+=(time_diff)*(time_diff);
	}
	
	double time_avg,time_std_dev,a_avg,a_std_dev;
	time_avg=(time_sum/(M-1));  //getting the average value of T
	time_std_dev=sqrt((((time_sq_sum)/(M-1))-(pow(((time_sum)/(M-1)),2)))); //getting standard deviation of T
	a_avg=width/M; //Getting the average value of a
	a_std_dev=sqrt((((width_sq_sum)/M)-(pow((width/M),2)))); // getting standard deviation of a
	printf("%lf %lf %lf %lf \n",time_avg,a_avg,time_std_dev,a_std_dev);
	free(points_arr);
	free(time_arr);
	free(noiseless);
	return 0;
}
	
	

