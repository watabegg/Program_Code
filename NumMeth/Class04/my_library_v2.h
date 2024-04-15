#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H
/* my_library version 2.0 */
void irekae(double a[][N + 1], int i, int n){
    int m, j, k;
    double key;
    m = i;

    /*　絶対値の最大のものを探す */
    for (k = i + 1; k <= n; k++){
        if (fabs(a[m][i]) < fabs(a[k][i])){
            m = k;
        }
    }
    
    /* 第 m　行と第　i 行 を入れ替える */
    for (j = 1; j <= n + 1; j++){
        key = a[m][j];
        a[m][j] = a[i][j];
        a[i][j] = key;
    }
}
// makes matrix "a" upper triangular by Gaussian elimination // n is the number of rows
int gaussian_elimination(double a[][N + 1], int n){
    double p, q;
    int i, j, k;
    /*対角成分より下を掃き出して上三角行列の形に変形*/
    for (i = 1; i <= n; i++){
        irekae(a, i, n);
        p = a[i][i];
        if (fabs(p) < 1.0e-6){
            printf("一意解をもちません\n");
            return -1;
        }
        /* 第　i 行を(i,i)成分で割る */
        for (j = i; j <= n + 1; j++){
            a[i][j] = a[i][j] / p;
        }
        for (k = i + 1; k <= n; k++){
            q = a[k][i];
            for (j = 1; j <= n + 1; j++){
                a[k][j] = a[k][j] - a[i][j] * q;
            }
        }
    }
    return 0;
}
// requires "a" to be an upper triangular matrix
// x is the output vector
// n is the number of rows
void inverse_substitution(double a[][N + 1], double x[N], int n){
    int i, j;
    double s;

    /*逆進代入による計算*/
    for (i = n; i >= 1; i--){
        s = 0.0;
        for (j = i + 1; j <= n; j++){
            s += a[i][j] * x[j];
        }
        x[i] = a[i][n + 1] - s;
    }
}

/*行列の入力*/
int input_matrix(double a[N][N]){
    int n, i, j;
    char z, zz;

    while (1){
        printf("行列の次数の入力 (1 < n < %d) n = ", N - 1);
        scanf("%d%c", &n, &zz);

        if ((n <= 1) || (N - 1 <= n))
            continue;

        printf("\n行列Aの成分を入力します\n\n");

        for (i = 1; i <= n; i++){
            for (j = 1; j <= n; j++){
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
void print_matrix(double a[N][N], int n){
    int i, j;
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            printf(" %10.6lf", a[i][j]);
        }
        printf("\n");
    }
}
#endif
