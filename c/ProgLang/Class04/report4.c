#include<stdio.h>
#define SIZE 10

//配列を表示するときはこれを利用する．
void print_array(int arg_data[SIZE]) {
    printf("[ ");
    for(int n = 0; n < SIZE; n++) {
        printf("%d ", arg_data[n]);
    }
    printf("]\n");
}

int main(void) {
    int data[SIZE] = { 1, 5, 8, 3, 10, 1, 5, 8, 3, 10 };

    /* ここから */
    int* p = data; //dataのポインタ
    int listmax = SIZE; //dataの0でない要素数を保管

    int bool=0; //仕様2
    if(SIZE < 3 || SIZE > 100){ 
        printf("List Size Error");
        bool = 1;
    }
    for(int i = 0; i < SIZE; i++){
        if(*(p + i) < 1){
            printf("List Element Error");
            bool = 1;
            break;
        }
    }
    if(bool){
        return 1; //上記のエラーあれば終了
    }

    while(*(p + 1) != 0){ 
        //data[1]が0になると終了(for文でceli(log2(SIZE))回繰り返しても良い)
        print_array(data);
        for(int i = 1; i < listmax; i += 2){ 
            //dataの要素が0にならないところ(listmax)までiが奇数になるよう移動
            if(*(p + i) != 0){ 
                if(*(p + i + 1) != 0 && (i + 1) < SIZE){ 
                    //date[i+1]が0でないかつi+1<SIZEを確認
                    *(p + i + 1) += *(p + i); //data[i+1]にdata[i]を足し合わせ
                }
                *(p + i - 1) += *(p + i); //data[i-1]にdata[i]を足し合わせ
                *(p + i) = 0; //data[i]を0
            }
        }

        listmax = listmax - (listmax / 2); //dataの0でない要素数を計算
        for(int k = 0; k < listmax; k++){
            //要素を詰める
            int tmp = *(p + (2 * k)); 
            *(p + (2 * k)) = 0; 
            *(p + k) = tmp; 
        }
    }
    /* ここまで */
    
    print_array(data);
    return 0;
}