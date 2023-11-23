#include<stdio.h>
#define CARD_MAX 53
#define JOKER -1

void perfectShuffle(int *cards) {
    /* ここから */
    int left[CARD_MAX] = {}; //パーフェクトシャッフル左側
    int right[CARD_MAX] = {}; //パーフェクトシャッフル右側
    int num = CARD_MAX;

    for(int i = 0; i < CARD_MAX; i++){
        if(*(cards + i) == JOKER){
            num = i - 1; //JOKER手前を取得
        }
    }

    for(int i = 0; i < (num / 2) + 1; i++){
        *(right + i) = *(cards + i); //カード前半を取得
        *(left + (num / 2) - i + 1) = *(cards + num - i); //カード後半を取得
    }

    for(int i = 0; *(cards + i) != JOKER; i++){
        if(i % 2 == 0){
            *(cards + i) = *(right + (i / 2)); //カード合流
        }
        else{
            *(cards + i) = *(left + ((i + 2) / 2)); //カード合流
        }
    }

    /* ここまで */
    //1回シャッフルした時点のカードを表示
    int *now = cards;
    while(*now != JOKER) {
        printf("%d ", *(now++));
    }
    printf("\n");
}

int main(void) {
    int cards1[CARD_MAX] = {1,2,1,2,1,2,1,2,JOKER};
    int cards2[CARD_MAX] = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,JOKER};

    perfectShuffle(cards1);
    perfectShuffle(cards1);
    perfectShuffle(cards1); 
    perfectShuffle(cards2);
    perfectShuffle(cards2);
    perfectShuffle(cards2);
    perfectShuffle(cards2); 

    return 0;
}