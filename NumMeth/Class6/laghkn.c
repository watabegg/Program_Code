/**********************************************************************/
/* ���O�����W���̕�ԑ����� laghkn.c */
/**********************************************************************/
#include <stdio.h>
#define N 11
    int
    main(void)
{
    int i, j, k, n, np;
    double seki, xx, s, x[N], y[N], dx;
    char z, zz;
    while (1)
    {
        printf("���O�����W���̕�ԑ����� \n");
        printf("��ԓ_�̌�����͂��Ă�������(1 < n < 10) n = ");
        scanf("%d%c", &n, &zz);
        if ((n <= 1) || (10 <= n))
            continue;
        printf("\n ��ԓ_�̍��W����͂��Ă��������B \n");
        for (i = 1; i <= n; i++)
        {
            printf(" x(%d) = ", i);
            scanf("%lf%c", &x[i], &zz);
            printf(" y(%d) = ", i);
            scanf("%lf%c", &y[i], &zz);
            printf("\n");
        }
        printf("\n �������͂��܂������H (y/n) ");
        scanf("%c%c", &z, &zz);
        if (z == 'y')
            break;
    }
    printf("\n �w�肷��_���� �H np = ");
    scanf("%d%c", &np, &zz);
    dx = (x[n] - x[1]) / np;
    xx = x[1];
    for (i = 0; i <= np; i++)
    {
        s = 0.0;
        /*** �� Lk(x) �̌v�Z ***/
        for (k = 1; k <= n; k++)
        {
            seki = 1.0;
            /*** Lk(x) �̌v�Z ***/
            for (j = 1; j <= n; j++)
            {
                if (j != k)
                {
                    seki *= (xx - x[j]) / (x[k] - x[j]);
                }
            }
            s += seki * y[k];
        }
        printf("%10.6lf, %10.6lf \n", xx, s);
        xx += dx;
    }
    return 0;
}
