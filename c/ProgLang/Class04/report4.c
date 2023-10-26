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
    int* p = data; //dataのポインタ
    int* data_p; //書き換え用のポインタ
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
        return 1;
    }

    while(*(p + 1) != 0){ 
        //data[1]が0になると終了(for文でceli(log2(SIZE))回繰り返しても良い)
        print_array(data);
        for(int i = 1; i < listmax; i += 2){ 
            //listmaxになるまで1つ飛ばしで繰り返す(p+iがdataの奇数番目に来る為)
            data_p = p + i; //ポインタを奇数番目に移動
            if(*(data_p) != 0){ 
                if(*(data_p + 1) != 0 && (i + 1) < SIZE){ 
                    //date[i+1]が0でないかつi+1<SIZEを確認
                    *(data_p + 1) += *(data_p); //奇数番目を足し合わせ
                }
                *(data_p - 1) += *(data_p); //奇数番目を足し合わせ
                *(data_p) = 0; //奇数番目を0
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