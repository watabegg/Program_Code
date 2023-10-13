#include <stdio.h>
#include <stdbool.h>
#define DATA_LIM 5

int main(void) {
    /* 数列を表す配列 */
    int data[DATA_LIM] = { 1,2,3,4,0 };
    bool cover = true; //すべての添字を参照したか

    /* ここから */
    int sum_j = 0;
    int j = 0;

    for(int i = 0; i < DATA_LIM; i++){ 
        //dataの重複確認(重複があると必ずnot cover)
        for(int k = i + 1; k < DATA_LIM; k++){
            if(data[i] == data[k]){
                printf("data OverLap ERRER\n");
                cover = false;
                goto end; //多重ループから脱出したかったのでgoto
            }
        }
        if(data[j] >= DATA_LIM || DATA_LIM < 3 || DATA_LIM > 100){
            printf("UnExpected data ERRER\n"); //例外処理(DATA_LIMの範囲はついで)
            cover = false;
            goto end;
        }
        sum_j += data[j]; //添字の総和を計算
        printf("%d ", data[j]);
        j = data[j]; //添字を更新
    }
    end:
    printf("\n");

    if(sum_j != ((DATA_LIM - 1) * DATA_LIM) / 2){ 
        //添字参照の判定(coverの際，出力する添字は0~DATA_LIM-1の和になる)
        cover = false;
    }
    /* ここまで */

    if (!cover) {
        printf("not ");
    }
    printf("cover\n");

    return 0;
}