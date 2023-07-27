typedef struct struct_model
{
    int k;         /* ��{�֐��̐�k */
    int f_id[N];   /* ��{�֐���id 1,...,NF*/
    double sol[N]; /* ���f���̋��߂�a1,...ak�̌W�� */
    double err;    /* ���f���̌덷 */
} struct_model;
enum result
{
    TRUE,
    FALSE
};
int f_in_model(struct_model model, int fi)
{
    int i;
    int found = FALSE;
    for (i = 1; i <= model.k; i++)
    {
        if (fi == model.f_id[i])
        {
            found = TRUE;
            break;
        }
    }
    return found;
}
void copy_model(struct_model *p_current_m, struct_model *p_best_m)
{
    int j;
    (*p_best_m).err = (*p_current_m).err;
    (*p_best_m).k = (*p_current_m).k;
    for (j = 1; j <= (*p_best_m).k; j++)
    {
        (*p_best_m).f_id[j] = (*p_current_m).f_id[j];
        (*p_best_m).sol[j] = (*p_current_m).sol[j];
    }
}
void forward_step_wise_selection(int nf, double x[N], double y[N], int n,
                                 char *path, char *data)
{
    int i, k, j;
    struct_model current_m, best_m; /* ���s���f���ƍō����f�� */
    current_m.k = 0;
    current_m.err = DBL_MAX; /* DBL_MAX <float.h> */
    best_m.err = DBL_MAX;
    char fname_hokan[200], fname_out[200];
    FILE *fp_out;
    /* ���f���̌덷�Ɗ�{�֐��Ƌ��߂��W���̃t�@�C������ݒ肷�� */
    sprintf(fname_out, "%s/results/out_%s", path, data);
    /* ���f���̌덷�Ɗ�{�֐��Ƌ��߂��W���̃t�@�C�����J�� */
    fp_out = fopen(fname_out, "w");
    for (k = 1; k <= nf; k++) /* k basic functions */
    {
        printf("--- k = %d ---\n", k);
        for (i = 1; i <= nf; i++)
        {
            if (f_in_model(current_m, i) == FALSE)
            {
                /* ���݂̃��f���Ŋ֐�fi������ */
                current_m.k = k;
                current_m.f_id[k] = i;
                /* ���f���̌W�������߂� */
                compute_model(n, k, x, y, current_m.f_id, current_m.sol);
                /* ���f���̌덷�����߂� */
                current_m.err = model_error(n, k, x, y, current_m.sol,
                                            current_m.f_id);
                /* �ō����f�����X�V���� */
                if (current_m.err < best_m.err)
                    copy_model(&current_m, &best_m);
                /* �덷�Ƌ��߂���{�֐��̌W�����o�� */
                printf("%d %f ", i, current_m.err);
                for (j = 1; j <= k; j++)
                {
                    printf("%.3f*f%d ", current_m.sol[j], current_m.f_id[j]);
                }
                printf("\n");
            }
        }
        /* ���f���̌덷, ���f���̊�{�֐��Ƌ��߂��W�����o�� */
        model_error_output(fp_out, k, best_m.err, best_m.k, best_m.sol,
                           best_m.f_id);
        printf("k=%d �ō��̃��f��\n", best_m.k);
        printf(" �덷: %f\n", best_m.err);
        printf(" ���f��: ");
        for (j = 1; j <= best_m.k; j++)
        {
            printf("%.3f*f%d ", best_m.sol[j], best_m.f_id[j]);
        }
        printf("\n");
        /* �O���t��`�����߂̏��� (���\���o��) */
        sprintf(fname_hokan, "%s/results/mk%d_est_%s", path, best_m.k, data);
        // printf("%s\n", fname_hokan);
        data_output(fname_hokan, n, best_m.k, x, y, best_m.sol, best_m.f_id);
        /* ���݃��f�����X�V���� */
        copy_model(&best_m, &current_m);
    }
    /* �t�@�C������� */
    fclose(fp_out);
}