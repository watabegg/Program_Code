#include <stdio.h> 
#define _USE_MATH_DEFINES
#include <math.h> 

double f(double x, int i){
	//iの値に応じて適切なf(x)を呼び出す関数
	switch (i){
	case 0:
	case 1:
		return pow(x,4.0) - 3*x + 1;
	case 2:
		return cos(x) - x;
	case 3:
		return pow(M_E, x) - 1/x; 
	default:
		break;
	}
}
#define MAX_ITERATIONS 100 
double bisection(double a, double b, double eps, int i) { 
	double c; 
	int it = 0; 
	do { 
		c = (a+b)/2.0; //a,bを二分したx座標の値,cを用意
		if (f(a, i)*f(c, i) < 0.0) {  //符号が異なるとき
			b = c; 
		} 
		else {  //符号が一致するとき
			a = c; 
		}	 
		it++; 
		} while(fabs(b-a) >= eps && it <= MAX_ITERATIONS);  //a,bの差が2e-30より小さくなるか計算回数が100回を超えるときループを抜け出す
	c = (a+b)/2.0; 
	int func[] = {1,1,2,3};
	printf("function_%d it = %d \n", func[i], it); 
	
	return c; 
} 
int main() { 
	double date[4][2] = {{1.0, -1.0},{2.0, 1.0},{1.0, 0.0},{1.0, 0.0}};
	//各関数における解を含む閉区間の配列
	double epsilon = 2e-30; 
	for(int i = 0; i < 4; i++){
		//iの値で呼び出す関数と二分法を閉区間を変更できるように実装している
		double root = bisection(date[i][0],date[i][1],epsilon,i); 
		printf("a~b閉区間の解はx=%f , f(x) = %g\n", root, f(root,i));
	}
	
	return 0; 
}

