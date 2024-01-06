/*
ボードゲーム コヨーテ(PCソロプレイ用に改定)

自分以外のプレイヤーのカードを見て、その場のカードに書かれた数の合計を推理するゲーム。
最初のプレイヤーはその場のカードの合計が少なくともいくつであるかを宣言し、次に続くプレイヤーは
前のプレイヤーが宣言した以上の数字を宣言することでゲームが進む。
もし前のプレイヤーが宣言した数がこの場のカードの合計より大きいと思った場合「コヨーテ」と宣言することができる。
「コヨーテ」と宣言した場合、場のカードをすべて開示し、前のプレイヤーが宣言した数と場のカードの合計を比較する。
もし前のプレイヤーが宣言した数のほうが大きければ「コヨーテ」は成功。前のプレイヤーのライフが一つ減る。
もし前のプレイヤーが宣言した数が場のカードの合計より小さければ「コヨーテ」は失敗。「コヨーテ」を宣言したプレイヤーのライフが一つ減る。
これを繰り返し、ライフのなくなったプレイヤーが負けとなる。

詳細ルール
・使用されたカードは捨て札とする、ただしシャッフル0が出た際は次の場に行くときに捨て札と残った山札を混ぜ、プレイを再開する。
・x2は場の合計の数字を最後に2倍するカードである。
・MAX0は場の一番大きな数字を0にする。

ライフ:2
プレイヤー:4
カード内訳
1:4
2:4
3:4
4:4
5:4
10:3
15:2
20:1
0:3
シャッフル0:1
-5:2
-10:1
x2:1
MAX0:1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Players 4
#define CARDS 14

static int key[CARDS] = {0,1,2,3,4,5,10,15,20,-5,-10,200,100,199}; // 200:x2 100:MAX0 199:s0
static int value[CARDS] = {3,4,4,4,4,4,3,2,1,2,1,1,1,1};

typedef struct {
    int life;
    int card;
} player;

int Player_Move(player *p, int card, int prev){ // playerのデータを受け付けて行動決定
    printf("");
    int input;
    char str;
    int flag = 0;

    while(true){
        scanf("%s", &str);
        if(str == "y"){
            flag = 1;
            break;
        }
        else if(str == "n"){
            break;
        }
        else{
            printf("");
        }
    }
    if(flag){
        input = -1;
    }
    else{
        while(true){
            printf(":");
            scanf("%d", &input);
            if(input <= prev){
                printf("");
            }
            else(break);
        }
    }

    return input;
}

int Ai_Move(player *p){
}

int card_shaffule(int card_list){ // 山札をシャッフル
    srand((unsigned int)time(NULL));
    int size = sizeof(card_list) / sizeof(card_list[0]);

    for(int i = size - 1; i > 0; i--){
        int j = rand() % (i + 1);

        int tmp = card_list[i];
        card_list[i] = card_list[j];
        card_list[j] = tmp;
    }

    return card_list;
}

int generate_list(){ // シャッフルされていない山札を生成
    int num_cards = 0;

    for(int i = 0; i < CARDS; i++){
        num_cards += value[i];
    }
    int card_list[num_cards];

    for(int i = 0; i < CARDS; i++){
        int num = 0;
        int j = 0;
        for(j; j < value[i]; j++){
            card_list[num + j] = key[i];
        }
        num += j;
    }

    return card_list;

}

int card_dict(int key_input){ // 辞書型っぽいやつの関数
    int index;

    for(int i = 0; i < CARDS; i++){
        if(key_input == key[i]){
            index = i;
        }
        else{
            printf("Key Errer");
            return -1;
        }
    }

    return value[index];
}

int calc_sum(int hands[Players]){ // 場のカードの合計を計算する関数
    int sum = 0;
    int max = hands[0];
    int max_flag = 0;
    int double_flag = 0;
    int shuffle_flag = 0;
    for(int i = 0; i < Players; i++){
        switch (hands[i]){
        case 200: // x2のカードが場にある場合
            double_flag = 1;
            break;
        case 100: // MAX0のカードが場にある場合
            max_flag = 1;
            break;
        case 199: // シャッフル0のカードが場にある場合
            shuffle_flag = 1;
            break;
        default:
            if(hands[i] > max){ // カードの最大値を保存
                max = hands[i];
            }
            sum += hands[i];
            break;
        }
    }
    if(max_flag){ // フラグが立っていればMAXを消去
        sum -= max;
    }
    if(double_flag){ // フラグが立っていれば二倍
        sum = 2 * sum;
    }

    return max, shuffle_flag;
}

int play_main(player *p){
    srand((unsigned int)time(NULL));
    int card_list = card_shaffule(generate_list());
    int play_start = (rand() % Players);
    int turn = 0;

    while(p[0]->life && p[1]->life && p[2]->life && p[3]->life){ // コヨーテしたらここに戻る
        int playcard[Players];

        for(int i = 0; i < Players; i++){
            p[i].card = card_list[(turn * Players) + i];
            playcard[i] = p[i].card;
        }
        int prevnum = 0;
        int card_sum = calc_sum(playcard);
        while(true){ // プレイのためのループ
            int i = 0;
            int dec;
            int play_turn = (turn + i) % Players;
            if(play_turn == 3){
                dec = Player_Move(*p[3], playcard, prevnum);
                i += 1;
            }
            else{
                dec = Ai_Move(*p[play_turn]);
                i += 1;
            }
            if(dec == -1){

            }
            else{
                i += 1;
            }
        }
    }

}

int main(void){
    player p[Players];
    p[0]->life = 2;
    p[1]->life = 2;
    p[2]->life = 2;
    p[3]->life = 2;

}