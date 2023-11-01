#include<stdio.h>
#define DATA_NUM 8

void acmAvg(double data) {
    /* ここから */
    static double sum = 0;
    static double count = 0;
    sum += data; //dataの総和を保持する
    count += 1; //dataの個数を保持する
    /* ここまで */
    printf("%.3f\n", sum / count); //ここで平均値を出力する．dataの部分は変更してよい．
}

int main(void) {
    double data[DATA_NUM] = { 1.0, 5.0, 4.0, 5.0, 3.0, 4.0, 5.0, 3.0 };

    int i;
    for(i = 0; i < DATA_NUM; i++) {
        acmAvg(data[i]);
    }

    return 0;
}