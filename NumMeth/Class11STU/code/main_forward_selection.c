#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define N 220
#define NF 6 /* 基本関数の数*/
#include "my_library_v3.h"
#include "minjijo_lusolve_extended.h"
#include "forward_selection.h"
/* main_forward_selection */
int main(void)
{
    int n;             /* n個データ点数, */
    double x[N], y[N]; /* データ */
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
    printf("このプログラムは前方選択を使用して\n");
    printf("誤差が小さいモデルを見つ出す\n");
    /* データの入力 */
    sprintf(fname_data, "%s/data/%s", path, data);
    n = data_input(fname_data, x, y);
    /* 前方選択 */
    forward_step_wise_selection(NF, x, y, n, path, data);
    printf("モデル誤差と求めた基本関数の係数はファイル out_%s に保存されます\n", data);
    printf("補間結果はファイル mk#_est_%s に保存されます\n", data);
    printf("処理の終了\n");
    return 0;
}