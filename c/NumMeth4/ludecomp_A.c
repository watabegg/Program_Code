#include <stdio.h>
#include <math.h>
#define N 8
#include "my_library_v2.h"
int main(void){
    int i, j, n, k;
    double A = 1.0;
    static double p, q, a[N][N], l[N][N], u[N][N];

    /*** 行列の入力 ***/
    n = input_matrix(a);
    printf("入力：\n");
    print_matrix(a, n);
    printf("\n");
    /*LU分解とガウス消去*/
    for (i = 1; i <= n; i++){
        p = a[i][i];

        if (fabs(p) < 1.0e-6){
            printf("この行列はLU分解出来ません. \n");
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

        A *= l[i][i];
    }
    /*** 下三角行列Lの表示 ***/
    printf("L:\n");
    print_matrix(l, n);
    printf("\n");
    /*** 上三角行列Lの表示 ***/
    printf("U:\n");
    print_matrix(u, n);
    printf("A:%10.6lf" , A);
    return 0;
}
