#include<stdio.h>
#define SIZE 5

//配列を表示するときはこれを利用する．
void print_array(int arg_data[SIZE]) {
    printf("[ ");
    for(int n = 0; n < SIZE; n++) {
        printf("%d ", arg_data[n]);
    }
    printf("]\n");
}

int main(void) {
    int data[SIZE] = { 1, 5, 8, 3, 10 };

    /* ここから */
    int* p = data;
    int* data_p;
    bool loop = true;

    for(int i = 1; i < SIZE; i += 2){
        data_p = p + i;
    }
    

    /* ここまで */
    
    print_array(data);
    return 0;
}