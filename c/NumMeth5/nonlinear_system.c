#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS pow(10.0, -8.0) /* epsilonの設定*/
#define KMAX 100            /* 最大反復回数*/
#define N 4
#include "my_library_v3.h"
#include "nonlinear_system.h"
int main(void)
{
    double x, y, z;
    printf("初期値x0, y0, z0を入力してください----> x0 y0 z0\n");
    scanf("%lf %lf %lf", &x, &y, &z);
    int i, k = 0;
    double xk[N], d[N], J[N][N];
    double Jx[N]; /* ヤコビ行列の解 */
    xk[1] = x;
    xk[2] = y;
    xk[3] = z;
    do
    {
        /*右辺ベクトルの作成*/
        d[1] = -f(xk[1], xk[2], xk[3]);
        d[2] = -g(xk[1], xk[2], xk[3]);
        d[3] = -h(xk[1], xk[2], xk[3]);
        /*ヤコビ行列の作成*/
        J[1][1] = f_x(xk[1], xk[2], xk[3]);
        J[1][2] = f_y(xk[1], xk[2], xk[3]);
        J[1][3] = f_z(xk[1], xk[2], xk[3]);
        J[2][1] = g_x(xk[1], xk[2], xk[3]);
        J[2][2] = g_y(xk[1], xk[2], xk[3]);
        J[2][3] = g_z(xk[1], xk[2], xk[3]);
        J[3][1] = h_x(xk[1], xk[2], xk[3]);
        J[3][2] = h_y(xk[1], xk[2], xk[3]);
        J[3][3] = h_z(xk[1], xk[2], xk[3]);
        printf("Call lu_solve k= %d\n", k);
        lu_solve(3, J, d, Jx);
        for (i = 1; i <= 3; i++)
        {
            xk[i] += Jx[i];
        }
        k++;
    } while (vector_norm1(Jx) > EPS && k < KMAX);

    if (k == KMAX)
    {
        printf("答えが見つかりませんでした\n");
    }
    else
    {
        printf("回数%dで，答えはx=%f, y=%f, z=%fです\n", k + 1, xk[1], xk[2], xk[3]);
    }

    return 0;
}
