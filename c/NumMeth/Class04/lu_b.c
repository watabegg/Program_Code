#include <stdio.h>
#include <math.h>
#define N 8
#include "my_library_v2.h"
void input_vector(double b[N], int n){
    int i;
    char z, zz;

    while (1){
        printf("\n�s��A�̐�������͂��܂�\n\n");

        for (i = 1; i <= n; i++){
            printf("b(%d)=", i);
            scanf("%lf%c", &b[i], &zz);
        }

        printf("���������͂��܂������H(y/n)");
        scanf("%c%c", &z, &zz);
        if (z == 'y')
            break;
    }
}

void merge_coeff_rhs(double Lb[N][N+1], double l[N][N], double b[N], int n){
    int i, j;

    for(i = 1; i <= n; i++){
        for(j = 1; j <= n + 1; j++){
            if(j == n + 1){
                Lb[i][j] = b[i];
            }
            else {
                Lb[i][j] = l[i][j];
            }
        }
    }
}

void substitution(double a[][N + 1], double x[N], int n){
    int i, j;
    double s;

    /*���i����ɂ��v�Z*/
    for (i = 1; i <= n; i++){
        s = 0.0;
        for (j = i + 1; j <= n; j++){
            s += a[i][j] * x[j];
        }
        x[i] = a[i][n + 1] - s;
    }
}

int main(void){
    int i, j, n, k;
    static double p, q, a[N][N], l[N][N], u[N][N], b[N], b_dash[N], Lb[N][N+1], Ux[N][N+1], x[N];

    /*** �s��̓��� ***/
    n = input_matrix(a);
    input_vector(b, n);
    printf("���́F\n");
    print_matrix(a, n);
    printf("\n");
    /*LU�����ƃK�E�X����*/
    for (i = 1; i <= n; i++){
        p = a[i][i];

        if (fabs(p) < 1.0e-6){
            printf("���̍s���LU�����o���܂���. \n");
            return -1;
        }
        for (j = i; j <= n + 1; j++){
            l[j][i] = a[j][i];
            a[i][j] = a[i][j] / p;
        }

        for (k = i + 1; k <= n; k++){
            q = a[k][i];

            for (j = 1; j <= n + 1; j++){
                a[k][j] = a[k][j] - a[i][j] * q;
            }
        }
        for (j = i; j <= n; j++){
            u[i][j] = a[i][j];
        }
    }
    merge_coeff_rhs(Lb, l, b, n);
    substitution(Lb, b_dash, n);
    merge_coeff_rhs(Ux, u, b_dash, n);
    inverse_substitution(Ux, x, n);

    /*** ���O�p�s��L�̕\�� ***/
    printf("L:\n");
    print_matrix(l, n);
    printf("\n");

    /*** ��O�p�s��L�̕\�� ***/
    printf("U:\n");
    print_matrix(u, n);

    /*** ��x�̕\�� ***/
    printf("\n�A���������̉�\n\n"); 
	for(i=1; i<=n ; i++) { 
		printf("x( %d ) = %10.61f\n", i, x[i]); 
	} 
    return 0;
}
