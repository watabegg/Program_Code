#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define N 220
#define NF 6 /* ��{�֐��̐�*/
#include "my_library_v3.h"
#include "minjijo_lusolve_extended.h"
#include "forward_selection.h"
/* main_forward_selection */
int main(void)
{
    int n;             /* n�f�[�^�_��, */
    double x[N], y[N]; /* �f�[�^ */
    char *data = "example2.txt";
    // char *data="nh_covid-italy.txt";
    // char *data="nh_bb_age_weigth.txt";
    // char *data="nh_bb_age_length.txt";
    // char *data="nh_fish.txt";
    // char *data="nh_wine.txt";
    char *path =
        "/Users/hernan/Documents/Shindai/Lectures/Lectures-Mac-2023/Numerical
        Methods /
        Class11 ";
        char fname_data[200];
    printf("���̃v���O�����͑O���I�����g�p����\n");
    printf("�덷�����������f�������o��\n");
    /* �f�[�^�̓��� */
    sprintf(fname_data, "%s/data/%s", path, data);
    n = data_input(fname_data, x, y);
    /* �O���I�� */
    forward_step_wise_selection(NF, x, y, n, path, data);
    printf("���f���덷�Ƌ��߂���{�֐��̌W���̓t�@�C�� out_%s �ɕۑ�����܂�\n", data);
    printf("��Ԍ��ʂ̓t�@�C�� mk#_est_%s �ɕۑ�����܂�\n", data);
    printf("�����̏I��\n");
    return 0;
}