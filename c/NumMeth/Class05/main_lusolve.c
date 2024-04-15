#include <stdio.h>
#include <math.h>
#define N 8
#include "my_library_v3.h"
int main(void)
{
    int i, n;
    char zz;
    static double a[N][N], x[N], b[N];
    /*** 行列の入力 ***/
    n = input_matrix(a);

    printf("入力：\n");
    print_matrix(a, n);
    printf("\n");

    for (i = 1; i <= n; i++)
    {
        printf("b(%d)=", i);
        scanf("%lf%c", &b[i], &zz);
    }

    /*LU分解とガウス消去*/
    lu_solve(n, a, b, x); /*ax=b*/
    /*** 結果***/
    printf("x:\n");
    for (i = 1; i <= n; i++)
        printf("x[%d] = %f \n", i, x[i]);
    return 0;
}
