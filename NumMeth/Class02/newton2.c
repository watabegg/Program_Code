#include<stdio.h> 
#include<stdlib.h> 
#define _USE_MATH_DEFINES
#include<math.h> 

double f(double x, int i){ 
	//iの値に応じて適切なf(x)を呼び出す関数
	switch(i){
	case 0:
	case 1:
		return pow(x,4.0) -3*x +1; 
	case 2:
		return cos(x) - x; 
	case 3:
		return pow(M_E,x) -1/x; 
	case 4:
		return (pow(x,3.0) - pow(x,2.0)*3.0 +9.0*x - 8.0); 
	default:
		break;
	}
}

double f_prime(double x, int i){ 
	//iの値に応じて適切なf_prime(x)を呼び出す関数
	switch (i){
	case 0:
	case 1:
 		return 4.0 * pow(x,3.0) - 3; 
	case 2:
 		return -sin(x) - 1; 
	case 3:
 		return pow(M_E,x) + 1/pow(x,2); 
	case 4:
 		return (3.0*pow(x,2.0) - 6.0*x +9.0); 
	default:
		break;
	}
} 

#define EPSILON 0.000001 
double newton(double np, int i){ 
	int it = 0; 
 	double xk = np, xk1; 
 	while(1){ 
 		it++; 
 		xk1 = xk - f(xk, i)/f_prime(xk, i);
		// 一次近似y=f(a)+f'(a)(x-a)においてy=0とし式を変換し近似して得られた式
 		printf("Try %d Solution %.7f \n",it, xk1);  
 			if(fabs(xk1 - xk) < EPSILON){ //二数の差が0.000001以下になるまで繰り返す
				break; 
 			} 
 		xk = xk1; 
 		}	 
 	return xk; 
	}
int main(){ 
	int i = 0;
 	double initial_array[] = {1.0, -1.0, -1.0, 0.5, -1.0}; 
	int func[] = {1,1,2,3,4};
	//x_0となる数の配列、ここが初期地点となる。
	for(i; i < 5; i++){
		//iの値で呼び出す関数とニュートン法を始める初項を変更できるように実装している
 		printf("%d_function Final Solution %.6f \n", func[i], newton(initial_array[i], i));
	}
	 
	return 0; 
}

