#include<stdio.h>
#define SIZE 5

int main(void) {
    int src[SIZE] = { 1, 5, 4, 9, 6 };
    int dst[SIZE];

    /* ここから */
    // for(int i = 0; i < SIZE; i++){
    //     *(dst + i) = *(src + SIZE - i - 1);
    // }
    for(int i = 0; i < SIZE; i++){
        dst[i] = src[SIZE - 1 - i];
    }
    /* ここまで */

    int n;
    printf("dst=[ ");
    for(n = 0; n < SIZE; n++) {
        printf("%d ", dst[n]);
    }
    printf("]\n");

    return 0;
}