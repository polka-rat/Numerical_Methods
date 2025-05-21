/* 
Roll no.: EE23B022
Name:Deepak Charan S
Date: 24 October 2023
Version: 1.1
Description: Using the data given in the previous assignment to find the cubic spline interpolation
Input: number of points, x0
Output:  cubicSplineFunction(x0)
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void tridiagonal(float x[], float y[], int n, float e[], float f[], float g[], float r[]);
void interpol(float x[], float y[], int n, float d2x[], float xu, float *yu, float *dy, float *d2y);
void decomp_subst(float e[], float f[], float g[], float r[], int p, float d2x[]);
float f(float);

int main(int argc, char **argv)
{ 
  int order = atoi(argv[1]);
  int n = order + 1;
  float x_start = -1.0;
  float x_end = 1.0;
  float x_0 = atof(argv[2]);
  float x[n];
  float y[n];

  //to create initial data points from user inputs of start, end, and order
  for (int i = 0; i < n; i++) {
    x[i] = x_start + i * (x_end - x_start) / ((float)order);
    y[i] = f(x[i]);
  }

  float e[n];   //e, f, g, r - arrays in which tridiag coefficients are stored;
  float f[n];
  float g[n];
  float r[n];
  float d2x[n];
  float y_0, dy, d2y; //y value at x_0, i.e, what we ultimately need to find

  tridiagonal(x, y, n, e, f, g, r);
  decomp_subst(e, f, g, r, n-1, d2x);
  interpol(x, y, n, d2x, x_0, &y_0, &dy, &d2y);
  
  printf("%f\n", y_0);
  return 0;
}

float f(float x)  //polynomial through which we get y coordinates
{ 
  return 1 / (1 + (25 * pow(x, 2))); 
}

void tridiagonal(float x[], float y[], int n, float e[], float f[], float g[], float r[])  //generating a matrix
{
  f[1] = 2 * (x[2] - x[0]);
  g[1] = x[2] - x[1];
  r[1] = 6 / (x[2] - x[1]) * (y[2] - y[1]);
  r[1] = r[1] + 6 / (x[1] - x[0]) * (y[0] - y[1]);

  for (int i = 2; i < n - 2; i++)
  {
    e[i] = x[i] - x[i - 1];
    f[i] = 2 * (x[i + 1] - x[i - 1]);
    g[i] = x[i + 1] - x[i];
    r[i] = 6 / (x[i + 1] - x[i]) * (y[i + 1] - y[i]);
    r[i] = r[i] + 6 / (x[i] - x[i - 1]) * (y[i - 1] - y[i]);
  }
  e[n - 1] = x[n - 1] - x[n - 2];
  f[n - 1] = 2 * (x[n] - x[n - 2]);
  r[n - 1] = 6 / (x[n] - x[n - 1]) * (y[n] - y[n - 1]);
  r[n - 1] = r[n - 1] + 6 / (x[n - 1] - x[n - 2]) * (y[n - 2] - y[n - 1]);
}

void interpol(float x[], float y[], int n, float d2x[], float xu, float *yu, float *dy, float *d2y) //interpolating the value
{
  int flag = 0;
  int i = 1;

  while (1)
  {
    if (xu >= x[i - 1] && xu <= x[i])
    {
      float c1, c2, c3, c4, t1, t2, t3, t4;
      c1 = d2x[i - 1] / (6.0 * (x[i] - x[i - 1]));
      c2 = d2x[i] / (6.0 * (x[i] - x[i - 1]));
      c3 = (y[i - 1] / (x[i] - x[i - 1]) - d2x[i - 1] * (x[i] - x[i - 1])) / 6.0;
      c4 = (y[i] / (x[i] - x[i - 1]) - d2x[i] * (x[i] - x[i - 1])) / 6.0;

      t1 = c1 * pow(x[i] - xu, 3);
      t2 = c2 * pow(xu - x[i - 1], 3);
      t3 = c3 * (x[i] - xu);
      t4 = c4 * (xu - x[i - 1]);

      *yu = t1 + t2 + t3 + t4;
      t1 = -3.0 * c1 * pow(x[i] - xu, 2);
      t2 = 3.0 * c2 * pow(xu - x[i - 1], 2);
      t3 = -c3;
      t4 = c4;

      *dy = t1 + t2 + t3 + t4;
      t1 = 6 * c1 * (x[i] - xu);
      t2 = 6 * c2 * (xu - x[i - 1]);
      *d2y = t1 + t2;
      flag = 1;
    }
    else
    {
      i++;
    }

    if (i == n + 1 || flag == 1)
      break;
  }

  if (flag == 0)
  {
    printf("Outside range\n");
  }
}

void decomp_subst(float e[], float f[], float g[], float r[], int p, float d2x[])  //decomp_subst - calculates values of all double derivatives using LU decomposition using thomas algorithm
{
  // decomposition
  for (int i = 2; i <= p; i++)
  {
    e[i] = e[i] / f[i - 1];
    f[i] = f[i] - e[i] * g[i - 1];
  }

  // forward substitution
  for (int i = 2; i <= p; i++)
  {
    r[i] = r[i] - e[i] * r[i - 1];
  }

  // back substitution
  d2x[p] = r[p] / f[p];
  for (int i = p - 1; i >= 1; i--)
  {
    d2x[i] = (r[i] - g[i] * d2x[i + 1]) / f[i];
  }
}
