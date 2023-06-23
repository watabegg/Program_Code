/*L1-ノルム*/
double vector_norm1(double a[N + 1])
{
    int i = 0;
    double norm = 0.0;
    for (i = 1; i <= N; i++)
    {
        norm += fabs(a[i]);
    }
    return norm;
}
/*行列の入力*/
int input_matrix(double a[N][N])
{
    int n, i, j;
    char z, zz;
    while (1)
    {
        printf("行列の次数の入力 (1 < n < %d) n = ", N - 1);
        scanf("%d%c", &n, &zz);
        if ((n <= 1) || (N - 1 <= n))
            continue;
        printf("\n行列Aの成分を入力します\n\n");
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                printf("a(%d, %d)=", i, j);
                scanf("%lf%c", &a[i][j], &zz);
            }
            printf("\n");
        }
        printf("正しく入力しましたか？(y/n)");
        scanf("%c%c", &z, &zz);
        if (z == 'y')
            break;
    }
    return n;
}
/*行列の出力*/
void print_matrix(double a[N][N], int n)
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf(" %10.6lf", a[i][j]);
        }
        printf("\n");
    }
}
/*LU分解*/
int ludecomp(int n, double a[N][N], double l[N][N], double u[N][N])
{
    int i, j, k;
    double p, q;
    /*LU分解とガウス消去*/
    for (i = 1; i <= n; i++)
    {
        p = a[i][i];
        if (fabs(p) < 1.0e-6)
        {
            printf("この行列はLU分解出来ません. \n");
            return -1;
        }
        for (j = i; j <= n; j++)
        {
            l[j][i] = a[j][i];
            a[i][j] = a[i][j] / p;
        }
        for (k = i + 1; k <= n; k++)
        {
            q = a[k][i];
            for (j = 1; j <= n + 1; j++)
            {
                a[k][j] = a[k][j] - a[i][j] * q;
            }
        }
        for (j = i; j <= n; j++)
        {
            u[i][j] = a[i][j];
        }
    }
    return 0;
}
/*LU分解による連立一次方程式の解*/
int lu_solve(int n, double a[N][N], double b[N], double x[N])
{
    int i, j;
    double l[N][N] = {0}, u[N][N] = {0};
    double y[N] = {0};
    /*LU分解*/
    int ret = ludecomp(n, a, l, u);
    if (ret != 0)
    {
        return ret;
    }
    /*前進代入*/
    for (i = 1; i <= n; i++)
    {
        double py = b[i];
        for (j = 1; j < i; j++)
        {
            py -= l[i][j] * y[j];
        }
        y[i] = py / l[i][i];
    }
    /*後退代入*/
    for (i = n; i >= 1; i--)
    {
        double px = y[i];
        for (int j = i + 1; j <= n; j++)
        {
            px -= u[i][j] * x[j];
        }
        x[i] = px / u[i][i];
    }
    return 0;
}
