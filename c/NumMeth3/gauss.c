#include <stdio.h> 
#include <math.h> 

#define N 10 

#include "my_library.h" 

int main(void) { 
	int n,i,j; 
	static double a[N][N+1], x[N]; 
	//static double a[N][N+1] = {{0.0,0.0,0.0,0.0,0.0},{0.0,2.0,3.0,-1.0,1.0},{0.0,1.0,1.0,2.0,0.0},{0.0,3.0,-1.0,1.0,2.0}};
	char z, zz; 
	
	//n = 3;

	while(1) { 
		printf("�K�E�X�̏����ɂ��A���������̉�@\n"); 
		printf("�����A���@�莮�ł��� (1 < n < 9) n = "); 
		scanf("%d%c",&n, &zz); 
		if ((n <= 1) || (N-1 <= n)) continue; 
		printf("\n�W������͂��Ă�������\n\n"); 
		for(i=1;i<=n;i++) { 
			for(j=1; j<=n+1; j++) { 
				printf("a(%d, %d)=", i, j); 
				scanf("%lf%c",&a[i][j], &zz); 
			} 
			printf("\n"); 
		} 
		printf("���������͂��܂������H(y/n)"); 
		scanf("%c%c", &z, &zz); 
		if (z == 'y') break; 
	} 

	int ret = gaussian_elimination(a, n); 
	if (ret != 0) { 
		return ret; 
	} 
	inverse_substitution(a, x, n); 

	// ���̕\�� 
	printf("\n�A���������̉�\n\n"); 
	for(i=1; i<=n ; i++) { 
		printf("x( %d ) = %10.61f\n", i, x[i]); 
	} 
	return 0; 
}