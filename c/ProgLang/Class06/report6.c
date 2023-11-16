#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define COUNT_MAX 10 //入力回数制限

int main(void) {
    srand((unsigned int)time(NULL));
    int ans = rand() % 1000;
    int res;
    int count;

    printf("0~999の整数を当てよう！！\n\n");

    do {
        printf("いくつかな：");
        scanf("%d", &res);

        if (res > ans){ //入力が答えより大きいとき
            printf("大きすぎます\n");
        }
        else if (res < ans){ //入力が答えより大きいとき
            printf("小さすぎます\n");
        }
        count += 1;
        if(count >= COUNT_MAX){ //回数超えたらwhile脱出
            break;
        }

    } while (res != ans);

    if(count >= COUNT_MAX){
        printf("回数制限を超えました！正解は%dでした。\n", ans);
    }
    else{
        printf("正解です！正解は%dでした\n", ans);
    }

    return 0 ;
}