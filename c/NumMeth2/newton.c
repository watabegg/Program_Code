#include<stdio.h> 
#include<stdlib.h> 
#define _USE_MATH_DEFINES
#include<math.h> 

double f1(double x){ 
 	return pow(x,4.0) -3*x +1; 
} 

double f1_prime(double x){ 
 	return 4 * pow(x,3.0) - 3; 
} 

double f2(double x){ 
 	return cos(x) - x; 
} 

double f2_prime(double x){ 
 	return -sin(x) - 1; 
} 

double f3(double x){ 
 	return pow(M_E,x) -1/x; 
} 
double f3_prime(double x){ 
 	return pow(M_E,x) + 1/pow(x,2); 
} 

double f4(double x){ 
 	return (pow(x,3.0) - pow(x,2.0)*3.0 +9.0*x - 8.0); 
} 

double f4_prime(double x){ 
 	return (3.0*pow(x,2.0) - 6.0*x +9.0); 
} 
#define f(x) f4(x) 
#define f_prime(x) f4_prime(x) 
#define EPSILON 0.000001 
double newton(double np){ 
	int i = 0; 
 	double xk = np, xk1; 
 	while(1){ 
 		i++; 
 		xk1 = xk - f(xk)/f_prime(xk); 
 		printf("Try %d Solution %.7f \n", i, xk1);  
 			if(fabs(xk1 - xk) < EPSILON){ 
				break; 
 			} 
 		xk = xk1; 
 		}	 
 	return xk; 
	}
int main(){ 
 	double initial_value = -1.0; 
 	printf("Final Solution %.6f \n", newton(initial_value));  
	 
	return 0; 
}

