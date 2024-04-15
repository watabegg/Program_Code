#ifndef MY_LIBRARY_H 
#define MY_LIBRARY_H 

void irekae(double a[][N+1], int i, int n) { 
	int m, j, k; 
	double key; 
	m = i; 
	
	/*　絶対値の最大(最小)のものを探す */ 
	for(k=i+1; k<=n;k++) { 
		if (fabs(a[m][i]) > fabs(a[k][i])) { 
			m = k; 
		} 
	} 
	
	/* 第 m　行と第　i 行 を入れ替える */ 
	for(j=1; j<=n+1; j++) { 
		key = a[m][j]; 
		a[m][j] = a[i][j]; 
		a[i][j] = key; 
	} 
} 

// makes matrix "a" upper triangular by Gaussian elimination // n is the number of rows 

int gaussian_elimination(double a[][N+1], int n) { 
	double p,q; 
	int i,j,k; 
	/*対角成分より下を掃き出して上三角行列の形に変形*/ 
	for(i=1; i<=n; i++) { 
		irekae(a,i,n); 
		p = a[i][i]; 
		if (fabs(p) < 1.0e-6) { 
			printf("一意解をもちません\n"); 
			return -1; 
		} 
		/* 第　i 行を(i,i)成分で割る */ 
		for(j=i; j<=n+1; j++) { 
			a[i][j] = a[i][j] / p; 
		} 
		for(k=i+1; k<=n; k++) { 
			q = a[k][i]; 
			for(j=1; j<=n+1; j++) { 
				a[k][j] = a[k][j] - a[i][j] * q; 
			} 
		} 
	} 
	return 0; 
}

// requires "a" to be an upper triangular matrix 
// x is the output vector 
// n is the number of rows 

void inverse_substitution(double a[][N+1], double x[N], int n) { 
	int i,j; 
	double s; 
	/*逆進代入による計算*/ 
	for(i=n; i>=1; i--) { 
		s = 0.0; 
		for(j=i+1; j<=n; j++) { 
			s += a[i][j] * x[j]; 
		} 
		x[i] = a[i][n+1] - s; 
	} 
} 
#endif

