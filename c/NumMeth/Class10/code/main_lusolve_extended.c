#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define N 220
#include "my_library_v3.h"
#include "minjijo_lusolve_extended.h"
int main(void)
{
    int n;               /* n�f�[�^�_��, */
    double x[N], y[N];   /* �f�[�^ */
    int k, f_id[N];      /* ���f���F��{�֐��̐�k�A��{�֐���id */
    double sol[N] = {0}; /*���߂��̃��f���W��a1,...ak*/
    double err;          /* ���f���̌덷*/
    int m;               /*�@���ׂ郂�f�����@*/
    /* �f�[�^�t�@�C���@*/
    //char *data = "example2.txt";
    //char *data="nh_covid-italy.txt";
    // char *data="nh_bb_age_weigth.txt";
    // char *data="nh_bb_age_length.txt";
    // char *data="nh_fish.txt";
    char *data="nh_wine.txt";

    char *path =
        "C:/Program_code/NumMeth/Class10STU";

        /* �t�@�C�����������ϐ��@*/
        char fname_data[200],
         fname_models[200], fname_hokan[200],
         fname_out[200];
    /* �t�@�C���|�C���^�������ϐ��@*/
    FILE *fp_models, *fp_out;

    /* �f�[�^�t�@�C������ݒ肷��@*/
    sprintf(fname_data, "%s/data/%s", path, data);
    /*�@���f���̎d�l�t�@�C����ݒ肷�� */
    sprintf(fname_models, "%s/data/models.txt", path);
    /* ��Ԍ��ʃt�@�C����ݒ肷��@*/
    sprintf(fname_out, "%s/results/out_%s", path, data);
    /* ���f���̎d�l�t�@�C�����J��*/
    fp_models = fopen(fname_models, "r");
    /* ���f���̎d�l�t�@�C�����J��*/
    fp_out = fopen(fname_out, "w");

    printf("���̃v���O�����͍ŏ�2��@�ɂ���ā@\n");
    printf("y = a1*f1(x) + a2*f2(x) +...+ ak*fk(x) \n");
    printf("�̌`�̋Ȑ������Ă͂߂���̂ł��D\n\n");
    /*** �f�[�^�̓��� ***/
    n = data_input(fname_data, x, y);
    printf("%s �t�@�C������ %d �f�[�^�_����ǂݍ���\n", data, n);
    /* ���ׂ郂�f���̐���ǂݍ��� */
    fscanf(fp_models, "%d", &m);
    printf("models.txt�t�@�C������ %d ���f���𒲂ׂ�\n", m);
    /* models.txt �t�@�C���Ŏw�肳�ꂽ�e���f���𒲂ׂ�@*/
    for (int i = 1; i <= m; i++)
    {
        /* ���f����ǂݍ��ށ@*/
        k = read_model(fp_models, f_id);
        printf("m%d k %d ", i, k);
        /* ���f���̌W�������߂�@*/
        compute_model(n, k, x, y, f_id, sol);
        /* ���f���̌덷�����߂�@*/
        err = model_error(n, k, x, y, sol, f_id);
        printf("err %lf\n", err);
        /*�@���f���̌덷, ���f���̊�{�֐��Ƌ��߂��W�����o�� */
        model_error_output(fp_out, i, err, k, sol, f_id);
        /* ��Ԍ��ʃt�@�C����ݒ肷��@*/
        sprintf(fname_hokan, "%s/results/m%d_est_%s", path, i, data);
        /*�@��Ԍ��ʃt�@�C���@: �O���t��`�����߂̏��� (���\���o��) */
        data_output(fname_hokan, n, k, x, y, sol, f_id);
    }
    fclose(fp_models);
    fclose(fp_out);
    printf("���f���덷�Ƌ��߂���{�֐��̌W���̓t�@�C�� out_%s �ɕۑ�����܂�\n", data);
    printf("��Ԍ��ʂ̓t�@�C�� m#_est_%s �ɕۑ�����܂�\n", data);
    printf("�����̏I��\n");
}