/*
Roll No:EE23B022
Name:Deepak Charan S
Date:3.11.23
Version:1.0
Description: Use equations from Mallinson's paper, to solve for the trajectory theta(t) and phi(t) for  M on the unit sphere
Input:theta_start, theta_stop, alpha, delta_t
Output:  alpha, delta_t, R^2_Euler, R^2 Heun
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define gamma 1.76*pow(10,10)     //Values Got from Malinson's paper
#define H pow(10,-10)
#define pi M_PI
#define gold_time 0.01
#define er 0.1



double slope(double theta,float alpha);  //function to get the slope at a point
double r_square(double av1, double* rk_arr,double* norm_arr,int rk_count,int norm_count,int inc);//Function to get r_square for Euler's Curve





int main(int argc,char* argv[]){
	double theta_start=atof(argv[1]);
	double theta_stop=atof(argv[2]);
	double alpha=atof(argv[3]);
	double delta_t=atof(argv[4]);
	int inc=delta_t/gold_time;
	
	double theta=theta_start;
	double phi=-1*(pi);
	
	double theta_sum=theta_start;
	double phi_sum=phi;	
	int theta_count=1,phi_count=1;
	
	double phi_slope=(gamma*H/(alpha*alpha+1));
	
	double* euler_arr=(double*)malloc(1000000*sizeof(double));
	double* heun_arr=(double*)malloc(1000000*sizeof(double));
	double* rk_arr=(double*)malloc(1000000*sizeof(double));
	
	FILE* fp1=fopen("EulerTheta.txt","w");
	FILE* fp2=fopen("EulerPhi.txt","w");
	FILE* fp3=fopen("EulerSphere.txt","w");
	
	float time=0; 
	if(theta_stop>pi || theta_start<=0){
		printf("Please give range of angles between 0 and pi!!\n");
		return 0;
	}
	while(theta<=theta_stop){            //Euler's Curve
		fprintf(fp1,"%f %lf\n",time,theta);
		euler_arr[theta_count-1]=theta;
		fprintf(fp2,"%f %lf\n",time,phi);
		fprintf(fp3,"%lf %lf %lf\n",sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
		
		if(phi>=pi){
			phi=-1*(pi);
			phi_sum+=phi;
		}
		else{
			phi+=phi_slope*delta_t;
			phi_sum+=phi;
		}
		phi_count++;
		theta+=slope(theta,alpha)*delta_t;
		theta_sum+=theta;
		theta_count++;
		time+=delta_t;
	}
	int euler_count=theta_count;
	double euler_theta_avg=theta_sum/theta_count;
	double euler_phi_avg=phi_sum/phi_count;
	
	FILE* fp4=fopen("HeunTheta.txt","w");	
	FILE* fp5=fopen("HeunPhi.txt","w");
	FILE* fp6=fopen("HeunSphere.txt","w");
	
	theta=theta_start;
	time=0;
	phi=(-1)*pi;
	theta_sum=theta;
	phi_sum=phi;	
	theta_count=1;
	phi_count=1;
	
	double old_slope,new_slope;
	double temp_theta=theta; 
	while(theta<=theta_stop){    //Heun's Curve
		fprintf(fp4,"%f %lf\n",time,theta);
		heun_arr[theta_count-1]=theta;
		fprintf(fp5,"%f %lf\n",time,phi);
		fprintf(fp6,"%lf %lf %lf\n",sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
		
		old_slope=slope(theta,alpha);
		temp_theta=theta+old_slope*delta_t;
		new_slope=slope(temp_theta,alpha);
		
		theta+=((old_slope+new_slope)/2)*delta_t;
		theta_sum+=theta;
		theta_count++;
		
		if(phi>=pi){
			phi=-1*(pi);
			phi_sum+=phi;
		}
		else{
			phi+=((phi_slope+phi_slope)/2)*delta_t; //since rate of change of phi is invariant of time
			phi_sum+=phi;  
		}
		phi_count++;
		time+=delta_t;
	}
	int heun_count=theta_count;
	
	double heun_theta_avg=theta_sum/theta_count;
	double heun_phi_avg=phi_sum/phi_count;
	
	theta=theta_start;
	time=0;
	phi=(-1)*pi;
	theta_sum=theta_start;
	phi_sum=phi;
	theta_count=1;
	phi_count=1;
	float rk_time=0;
	
	FILE* fp7=fopen("RK45Theta.txt","w");	
	FILE* fp8=fopen("RK45Phi.txt","w");
	FILE* fp9=fopen("RK45Sphere.txt","w");
	double k1,k2,k3,k4;
	
	while(theta<=theta_stop){   //RK45 curve
		fprintf(fp7,"%f %lf\n",rk_time,theta);
		rk_arr[theta_count-1]=theta;
		fprintf(fp8,"%f %lf\n",rk_time,phi);
		fprintf(fp9,"%lf %lf %lf\n",sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
		k1=slope(theta,alpha);
		k2=slope(theta+((gold_time*k1)/2),alpha);
		k3=slope(theta+((gold_time*k2)/2),alpha);
		k4=slope(theta+(gold_time*k3),alpha);
		
		if(phi>=pi){
			phi=-1*(pi);
			phi_sum+=phi;
		}
		else{
			phi+=((phi_slope+(phi_slope+phi_slope)*2+phi_slope)/6)*gold_time;  //since rate of change of phi is invariant of time
			phi_sum+=phi;
		}
		phi_count++;
		theta+=(k1+2*(k2+k3)+k4)*delta_t/6;
		theta_sum+=theta;
		theta_count++;
		rk_time+=gold_time;
		time+=delta_t;
	}
	int rk_count=theta_count;
	double rk_theta_avg=theta_sum/theta_count;
	double rk_phi_avg=phi_sum/phi_count;
	
	double r_square_h=r_square(rk_theta_avg,rk_arr,heun_arr,rk_count,heun_count,inc);
	double r_square_e=(rk_theta_avg,rk_arr,euler_arr,rk_count,euler_count,inc);
	
	//printf("%lf %lf %lf %lf\n",alpha,delta_t,r_square_e,r_square_h);
	//printf("%lf %f\n",alpha,rk_time);
	
	free(euler_arr);
	free(heun_arr);
	free(rk_arr);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
	fclose(fp7);
	fclose(fp8);
	fclose(fp9);
	
	return 0;
}

double slope(double theta,float alpha){    //function to get the slope at a point
	double val=((gamma*alpha)*(H*sin(theta))/(alpha*alpha+1));
	return val;
}

double r_square(double av1, double* rk_arr,double* norm_arr,int rk_count,int norm_count,int inc){   //function to get r_square for Heun's curve
    double sr1=0,sr2=0,st1=0,st2=0,x;
    int count1=0,count2=0;    
    
    while(count1<norm_count && count2<rk_count){
    	printf("%f\n",((norm_arr[count1]-rk_arr[count2])/norm_count));
      if(((norm_arr[count1]-rk_arr[count2])/norm_count)<er){
      sr1+=pow((norm_arr[count1]-rk_arr[count2]),2);
      st1=pow((norm_arr[count1]-av1),2);
      //printf("%lf %lf\n",norm_arr[count1],rk_arr[count2]);
      }
      count1++;
      count2++;
    }
    x=((st1-sr1)/st1);  //r_square for theta
    return x;
}


