/ 2

#include <stdio.h>
#define N 10
    int
    main(void)
{
    int i, j, n;
    double a[N][N], s, t, x;
    char z, zz;
    while (1)
    {
        printf("ニュートンの差商公式による補間\n");
        printf("補間の個数 n は？ (1<n<9) n=");
        scanf("%d%c", &n, &zz);
        if ((n <= 1) || (9 <= n))
            continue;
        printf("\n補間点の座標を入力してください\n");
        for (i = 0; i < n; i++)
        {
            printf(" x(%d)=", i);
            scanf("%lf%c", &a[i][0], &zz);
            printf(" y(%d)=", i);
            scanf("%lf%c", &a[i][1], &zz);
        }
        printf("\n正しく入力しましたか? (y/n)");
        scanf("%c%c", &z, &zz);
        if (z == 'y')
            break;
    }
    /*** 各階差商の計算 ***/
    /*** 第２階差商をa[i][2]へ入れる***/
    /*** 第３階差商をa[i][3]へ入れる***/
    for (j = 1; j <= n; j++)
    {
        for (i = 0; i <= n - j; i++)
        {
            a[i][j + 1] = (a[i + 1][j] - a[i][j]) / (a[i + j][0] - a[i][0]);
        }
    }
    while (1)
    {
        printf("指定する点は？ X= ");
        scanf("%lf%c", &x, &zz);
        s = a[0][1];
        t = 1;
        /*** 差商公式による計算 ***/
        for (j = 2; j <= n; j++)
        {
            t *= (x - a[j - 2][0]);
            s += a[0][j] * t;
        }
        /*** 答の表示 ***/
        printf("\n f(%10.6lf) = %10.6lf\n", x, s);
        printf("\n やめますか？ (y/n) ");
        scanf("%c%c", &z, &zz);
        if (z == 'y')
            break;
    }
    return 0;
}
