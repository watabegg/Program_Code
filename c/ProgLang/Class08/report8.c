#include <stdio.h>

#define LEN 256

int main(void) {
    char str[LEN]; /* 文字列を格納する配列 */
    int kaibun; /* 回文なら 1 そうでなければ 0 */

    /* 文字列の入力 */
    scanf("%s", str);

    /* 回文チェック　ここから */
    int num = -1;
    kaibun = 1;

    while(str[num + 1] != '\0'){
        num ++; // 文字の端のインデックスを取得
    }

    for(int j = 0; j <= (num / 2); j++){
        // printf("left:%c,right:%c\n", str[j], str[num-j]); // テスト用出力
        if(str[j] != str[num - j]){ //文字列の左右を比較して違ったらnot kaibun
            kaibun = 0;
            break; // もうどうせ回文ではないのでbreak
        }
    }
    /* ここまで */

    printf("%s is ", str);
    if ( !(kaibun) ) {
        printf("not ");
    }
    printf(" Kaibun.\n");

    return 0;
}