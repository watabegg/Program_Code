#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_LOW 0
#define LIMIT_HIGH 25

/* 構造体の定義 */
typedef struct tag {
    int temp;   /* 温度 */
    struct tag *prev; /* 1つ前のデータへのポインタ変数 */
    struct tag *next; /* 1つ後のデータへのポインタ変数 */
} tempData;       /* 温度データ */


/* 新データ作成関数 */
tempData* makeNewNode(int t) {
    tempData* pNewNode;
    /*** tempData 型のメモリ領域確保 ***/
    pNewNode = (tempData*)malloc(sizeof(tempData));
    if (pNewNode != NULL) {
        /*** データ設定 ***/
        pNewNode->temp= t;
        pNewNode->prev = NULL;
    pNewNode->next = NULL;
    }
  return pNewNode ;
}


int main(void) {
    int temp; /* 温度入力用変数 */
    tempData *pTop;  /* 温度データリストのトップ */
    tempData *pLast;  /* 温度データリストの末尾 */
    tempData *pNow;  /* 温度データリスト内の現在位置 */
    tempData *pNew;  /* 温度データの新規データ */
    /* 必要であれば，ここに変数を追加 */

    /* 最初のデータは，必ず範囲内のデータであるとする */
    scanf("%d", &temp);
    pTop = makeNewNode(temp);
    pLast = pTop;

    /* 次のデータを入力 */
    scanf("%d", &temp);
    while ( (LIMIT_LOW <= temp) && (temp <= LIMIT_HIGH)) {
        /* データ作成 */
        pNew = makeNewNode(temp);

        /* 先頭データより小さいか？ */
        if (pNew->temp < pTop->temp) {
            /* 先頭の入れ替え */
            pNew->next = pTop; // pNew-nextにpTopのアドレス紐づけ
            pTop->prev = pNew; // pTop-prevにpNewのアドレス紐づけ
            pTop = pNew; // pTop更新
        } else {
            /* 挿入する場所を探す */
            pNow = pTop;
            /* 末尾に達するまで探す */
            while (pNow != pLast) {
                /* 1つ先のデータが pNew より大きかったら，そこが挿入ポイント */
                if (pNew->temp < pNow->next->temp) {
                    /* 挿入処理 */
                    pNew->prev = pNow;
                    pNew->next = pNow->next;
                    pNow->next = pNew;
                    pNew->next->prev = pNew;
                    /* 探索終了 */
                    break;
                }
                pNow = pNow->next;
            }
            /* 探索が末尾に達して終了したら，末尾に追加 */
            if (pNow == pLast) {
                /* 末尾に追加 */
                pNew->prev = pLast; // pNew-prevにpLastのアドレス紐づけ
                pLast->next = pNew; // pLast-nextにpNewのアドレス紐づけ
                pLast = pNew; // pLastをpNewに更新
            }
        }
    
        /* 次のデータを入力 */
        scanf("%d", &temp);
    }

    /* 出力処理 */
    pNow = pLast;
    while (pNow != NULL) {
        printf("%d\n", pNow->temp);
        pNow = pNow->prev;
    }


    return 0 ;
}