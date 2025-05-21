/*
Roll No:EE23B022
Name: Deepak Charan S
Date: 15.10.2023
Version: 1.0
Description: 1.Generating normal distributions for noise eps_T, eps_a, n (Getting eps_T,eps_a using Box Muller Transformation)
	     2.Generating a time series of Lorentzians  s(t) separated by T with width proportional to a and adding noise to it	
	     3.Identifying the locations of the peaks and estimating T and a and applying a exponential filter on it
Input:in form of M,T,a,type of graph (type l for Lorentzian;g for Gaussian) in the respective order
Output: avg(T),avg(a),stdev(T),stdev(a) in the respective order

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define pi M_PI   
#define inc_coeff 0.1
#define tol 1.5
#define A 0.62   

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

int main(int argc, char* argv[]){
	if(argc==4){
		printf("Please enter 0 for Lorentzian or 1 for Gaussian \n");
		return 0;
	}
	int M=atoi(argv[1]); 
	double T=atof(argv[2]);
	double b=atof(argv[3]);
	int type=atoi(argv[4]);		
	srand(time(NULL));
	double max=(long double)RAND_MAX;  //Getting max value possible from a random number generation
	
	int count=0; //to get number of points in graph
	double u1,u2,a,point,exp_pow;

	
	FILE* fp1=fopen("ee23b022_realtimedata.txt","w");
	
	if(argv[4][0]=='l' || argv[4][0]=='L'){          //lorentzian curve
		for(int m=1;m<=M;m++){
			for(double time=((T*m)-(T/2));time<((T*m)+(T/2));time+=0.1){
				
				u1=rand()/max;
				u2=rand()/max;
				a=b;
				a+=a*box_cos(u1,u2);			 //adding noise to a
				point=(pow(a,2))/(pow(time-(m*T+box_sin(u1,u2)),2)+pow(a,2))+0.1*box_cos(u1,u2); //adding noise to T and overall functional value	
				fprintf(fp1,"%lf %lf \n",time,point);
			}
		}
	}
	else{  //gaussian curve
		for(int m=1;m<=M;m++){
			for(double time=((T*m)-(T/2));time<((T*m)+(T/2));time+=0.1){				
				u1=rand()/max;
				u2=rand()/max;
				a=b;
				a+=a*box_cos(u1,u2);			 //adding noise to a
				exp_pow=(-1)*((pow(time-(m*T+box_sin(u1,u2)),2))/(2*pow(a,2)));		 //adding noise to a
				point=1*exp(exp_pow)+inc_coeff*box_cos(u1,u2); //adding noise to T and overall functional value				
				fprintf(fp1,"%lf %lf \n",time,point);
			}
		}
	}	
	fclose(fp1);
	
	FILE* fp2=fopen("ee23b022_realtimedata.txt","r");
	FILE* fp3=fopen("ee23b022_realtime_noiselessdata.txt","w");
	double prev_point=0,noiseless_point,noisy_point;	
	float second=-1.0,first=-1.0,peak_time_1=-1.0,tim,peak_time_2;	
	double a_sum=0,a_sq_sum=0,time_sum=0,time_sq_sum=0;

	while(fscanf(fp2,"%f %lf",&tim,&noisy_point)!=-1){
		if(prev_point==0){  //for first point
			prev_point=noisy_point;
			fprintf(fp3,"%f %lf\n",tim,prev_point);
		}
		else{
			noiseless_point=((1-A)*prev_point)+(A*noisy_point);  //applying exponential filter
			fprintf(fp3,"%f %lf\n",tim,noiseless_point);
			prev_point=noiseless_point;
			if(noiseless_point<=0.5 && first!=-1.0 && (tim-first)>(a/tol)){  //finding the second intersection (and applying a tolerance condition to bypass cases where noise removal wasnt enough)
				second=tim;
				if(argv[4][0]=='l' || 'L'){
					a_sum+=(second-first)/2;  //width of a lorentzian curve
					a_sq_sum+=pow(((second-first)/2),2);
				}
				else{
					a_sum+=((second-first)/(2*sqrt(log(4)))); //width of a gaussian curve
					a_sq_sum+=pow(((second-first)/(2*sqrt(log(4)))),2);
				}
				if(peak_time_1==-1.0){
					peak_time_1=((first+second)/2);  //time at which a peak is attained
				}
				else{
					peak_time_2=((first+second)/2);
					time_sum+=peak_time_2-peak_time_1;
					time_sq_sum+=pow((peak_time_2-peak_time_1),2);
					peak_time_1=peak_time_2;	
				}
				first=-1.0;
			}
			else if(noiseless_point>=0.5 && first==-1.0){
				first=tim;
			}			
		}
	}
	float a_avg,a_std_dev,t_avg,t_std_dev;
	a_avg=a_sum/M; //average value of time
	a_std_dev=sqrt(fabs((((a_sq_sum)/M)-(pow(a_avg,2)))));  //std dev of a
	t_avg=(time_sum/(M-1)); //average value of time
	t_std_dev=sqrt(fabs((((time_sq_sum)/(M-1))-(pow(t_avg,2))))); //std dev of time
	printf("%f %f %f %f\n",t_avg,a_avg,t_std_dev,a_std_dev);
	return 0;
}
	
