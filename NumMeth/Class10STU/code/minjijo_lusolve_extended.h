/* ��{�֐�fi��x�ł̊֐��ly�����߂� */
double ffv(int fi, double x)
{
    double y;
    switch (fi)
    {
    case 1:
        y = 1.0;
        break;
    case 2:
        y = x;
        break;
    case 3:
        y = pow(x, 2);
        break;
    case 4:
        y = pow(x, 3);
        break;
    case 5:
        y = 1.0 / x;
        break;
    case 6:
        y = exp(x);
        break;
    default:
        y = x;
        break;
    }
    return y;
}
/*** �f�[�^�̓��� ***/
int data_input(char *fname, double x[N], double y[N])
{
    int n = -1, i;
    FILE *fp;

    fp = fopen(fname, "r");
    if (fp == NULL)
    {
        printf("�t�@�C���u%s�v���J�����Ƃ��ł��܂���", fname);
        exit(0);
    }
    /* �f�[�^�̌��͉��ł����H�i1< n < %d�jn = ", N); */
    fscanf(fp, "%d", &n);
    if ((n <= 1) || (N <= n))
        printf("�f�[�^�̌���(1< n < %d�j�łȂ���΂Ȃ�܂���, n = %d", N, n);

    /* printf("\n�f�[�^x�̒l�͏������̏��ɓ��͂���. \n"); */
    for (i = 1; i <= n; i++)
    {
        fscanf(fp, "%lf", &x[i]);
        fscanf(fp, "%lf", &y[i]);
    }

    fclose(fp);
    return n;
}
/*�@���f����ǂݎ��@*/
int read_model(FILE *fp_models, int f_id[N])
{
    int k = 0;
    char line[81], *token;
    /* ��{�֐�fk(x)���P�`k�̔ԍ���ǂݎ�� */
    /* �t�@�C���� 1 �s���當����Ƃ��ă��f���̎d�l��ǂݎ��@*/
    fgets(line, sizeof(line), fp_models);
    /* �󔒂ŋ�؂�ꂽ������ɕ��� */
    token = strtok(line, " ");
    while (token != NULL)
    {
        k++;
        /* �֐���ID�𕶎��񂩂琮���ɕϊ����� */
        f_id[k] = atoi(token);
        /* ���̊֐���ID���擾���܂� */
        token = strtok(NULL, " ");
    }
    /* ��{�֐��̐���Ԃ� */
    return k;
}
/* A[n][k],tA[k][n]��b[k]��ݒ肷�� */
void set_A_tA_b(int n, int k, int f_id[N], double x[N], double y[N], double A[N][N], double tA[N][N], double b[N])
{
    int i, j;
    /* �֐����Ăяo���AA��tA��ݒ肷�� */
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= k; j++)
        {
            A[i][j] = ffv(f_id[j], x[i]);
            tA[j][i] = A[i][j];
        }
        /* b��ݒ肷�� */
        b[i] = y[i];
    }
}
/* tA[k][n]�EA[n][k]���v�Z���Ĕz��tAA[k][k]�ɓ���� */
void seki_tA_A(int n, int k, double tA[N][N], double A[N][N], double tAA[N][N])
{
    int i, j, jj;
    double s;

    for (i = 1; i <= k; i++)
    {
        for (j = 1; j <= k; j++)
        {
            s = 0.0;
            for (jj = 1; jj <= n; jj++)
            {
                s = s + tA[i][jj] * A[jj][j];
            }
            tAA[i][j] = s;
        }
    }
}
/* tA[k][n]�Eb[k]���v�Z����tAb[k]�z��ɓ���� */
void seki_tA_b(int n, int k, double tA[N][N], double b[N], double tAb[N])
{
    double s;
    int i, j;
    tAb[0] = 0;
    for (i = 1; i <= k; i++)
    {
        s = 0.0;
        for (j = 1; j <= n; j++)
        {
            s = s + tA[i][j] * b[j];
        }
        tAb[i] = s;
    }
}
/* ���f���̌W�������߂�@*/
void compute_model(int n, int k, double x[N], double y[N], int f_id[N],
                   double sol[N])
{
    double A[N][N], tA[N][N], b[N], tAA[N][N], tAb[N];
    int i;

    for (i = 0; i <= k; i++)
        sol[i] = 0; /* ���߂�a1,...ak�̌W��������*/
    /* A[n][k],tA[k][n]��b[k]��ݒ肷�� */
    set_A_tA_b(n, k, f_id, x, y, A, tA, b);
    /* tA[k][n]�EA[n][k]���v�Z���Ĕz��tAA[k][k]�ɓ���� */
    seki_tA_A(n, k, tA, A, tAA);
    /* tA[k][n]�Eb[k]���v�Z����tAb[k]�z��ɓ���� */
    seki_tA_b(n, k, tA, b, tAb);
    /* LU����@�ŉ��� */
    lu_solve(k, tAA, tAb, sol);
}
/* ���f���̌덷�����߂�@*/
double model_error(int n, int k, double x[N], double y[N], double sol[N],
                   int f_id[N])
{
    int i, j;
    double err = 0.0, yy;

    for (i = 1; i <= n; i++)
    {
        yy = 0.0;
        for (j = 1; j <= k; j++)
        {
            yy += sol[j] * ffv(f_id[j], x[i]);
        }
        err += (yy - y[i]) * (yy - y[i]);
    }
    return err / n;
}
/*�@���f���̌덷, ���f���̊�{�֐��Ƌ��߂��W�����o�� */
void model_error_output(FILE *fp_out, int i, double err, int k, double sol[N], int f_id[N])
{
    int j;
    fprintf(fp_out, "%d\t%f", i, err);
    for (j = 1; j <= k; j++)
    {
        fprintf(fp_out, "\t%f*f%d", sol[j], f_id[j]);
    }
    fprintf(fp_out, "\n");
}
/*�@��Ԍ��ʃt�@�C���@: �O���t��`�����߂̏��� (���\���o��) */
void data_output(char *fname, int n, int k, double x[N], double y[N],
                 double sol[N], int f_id[N])
{
    double h, xx, yy;
    int i, j;
    FILE *fp;

    fp = fopen(fname, "w");
    if (fp == NULL)
    {
        printf("�t�@�C���u%s�v���J�����Ƃ��ł��܂���", fname);
        exit(0);
    }
    h = (x[n] - x[1]) / 500.0;
    xx = x[1];
    for (i = 0; i <= 500; i++)
    {
        yy = 0.0;
        for (j = 1; j <= k; j++)
            yy += sol[j] * ffv(f_id[j], xx);
        fprintf(fp, "%lf\t%lf\n", xx, yy);
        xx = xx + h;
    }
    fclose(fp);
}