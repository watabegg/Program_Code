
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define N 220
#define NF 11   /* 基本関数の数*/
#include "my_library_v3.h"
#include "minjijo_lusolve_extended.h"
#include "forward_selection.h"

/* main_forward_selection */
 int main(void)
 {
     int n_train, n_test;  /* n個データ点数,  */
     double x_train[N], y_train[N], x_test[N], y_test[N]; /* データ */

     char *data_train="data_poly_3_train.txt";
     char *data_test="data_poly_3_test.txt";


     char *path= "/Users/hernan/Documents/Shindai/Lectures/Lectures-Mac-2023/Numerical Methods/Class12";
     char fname_data_train[200];
     char fname_data_test[200];

     printf("このプログラムは前方選択を使用して\n");
     printf("誤差が小さいモデルを見つ出す\n");

     /* データの入力 */
     sprintf(fname_data_train,"%s/data/%s", path, data_train);
     n_train = data_input(fname_data_train, x_train, y_train);
     sprintf(fname_data_test,"%s/data/%s", path, data_test);
     n_test = data_input(fname_data_test, x_test, y_test);

     /* 前方選択 */
     //forward_step_wise_selection(NF, x_train, y_train, n_train, path, data_train);
     forward_step_wise_selection_train_test(NF, x_train, y_train, n_train, path, data_train, x_test,  y_test, n_test);
     
     printf("モデル誤差と求めた基本関数の係数はファイル out_%s に保存されます\n",data_train);
     printf("補間結果はファイル mk#_est_%s に保存されます\n", data_train);
     printf("処理の終了\n");
     
     return 0;
 }

 
 


 
