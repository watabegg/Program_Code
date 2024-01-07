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
MAX->0:1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Players 4
#define CARDS 14

int key[CARDS] = {0,1,2,3,4,5,10,15,20,-5,-10,200,100,199}; // 200:x2 100:MAX0 199:s0
int value[CARDS] = {3,4,4,4,4,4,3,2,1,2,1,1,1,1};

typedef struct {
    int life;
    char card[20];
} player;

int Player_Move(player *p, int prev){ // playerのデータを受け付けて行動決定
    printf("現在のプレイヤーの手札は\n");
    for(int i = 0; i < Players - 1; i++){
        printf("プレイヤー%d:%s ", i + 1, p[i]->card);
    }
    printf("\nです。\n\n");
    if(prev){
        printf("直前のプレイヤーは%dを宣言しています。\n", prev);
    }
    else{
        printf("あなたが最初のプレイヤーです。\n");
    }
    int input;
    char input_str[100];
    char str;
    int flag = 0;

    while(true){
        if(prev){
            printf("コヨーテを宣言しますか？(はい:y いいえ:n):");
            scanf("%s", &str);
            if(str == "y"){
                flag = 1;
                break;
            }
            else if(str == "n"){
                break;
            }
            else{
                printf("入力エラー yかnを入力してください");
            }
        }
        else{
            break;
        }
    }
    if(flag){
        printf("あなたはコヨーテを宣言しました。");
        input = -1;
    }
    else{
        while(1){
            printf("宣言する数字を入力してください:");
            fgets(input_str, sizeof(input_str), stdin);

            char *endptr;
            input = strtol(input_str, &endptr, 10);

            if(input_str[0] != '\n' && (*endptr == '\n' || *endptr == '\0') && input != 0 && input > prev){
                break;
            }
            else{
                printf("入力エラー 数値以外、もしくは前の宣言より小さい数字が入力されています。");
            }
        }
        printf("あなたは%dを宣言しました。", input);
    }

    return input;
}

int Ai_Move(player *p, int prev, int turn){
    int otherhand[Players] = {0};
    int guess = 5; // botの手札予想
    static int self_prev[Players - 1] = {0};
    int max_flag = 0;
    int double_flag = 0;
    int output;
    for(int i = 0; i < Players; i++){
        if(i != turn){
            otherhand[i] = p[i]->card;
            switch (p[i]->card){
                case 100:
                    max_flag = 1;
                    break;
                case 200:
                    double_flag = 1;
                    break;
                default:
                    break;
            }
        }
    }
    int other_sum = calc_sum(otherhand, CARDS);
    if(prev == 0){
        if(other_sum < 0){
            output = 1;
        }
        else{
            output = other_sum / 2;
        }
    }
    else{
        int interval = self_prev - prev;
        if(prev > (other_sum + guess)){
            if(interval > 3 && interval <= 5){
                guess = 10;
                if(prev >= (other_sum + guess)){
                    output = -1;
                }
                else{
                    output = (((other_sum + guess) - prev) / 2) + 1;
                }
            }
            else if(interval > 5 && interval <= 8){
                guess = 15;
                if(prev >= (other_sum + guess)){
                    output = -1;
                }
                else{
                    output = (((other_sum + guess) - prev) / 3) + 1;
                }
            }
            else if(interval > 8){
                guess = 20;
                if(prev >= (other_sum + guess)){
                    output = -1;
                }
                else{
                    output = (((other_sum + guess) - prev) / 5) + 1;
                }
            }
            else{
                output = 1;
            }
        }
        else{
            if(interval == 3){
            }
            else if(interval > 3 && interval <= 5){
            }
            else if(interval > 5 && interval <= 7){
            }
            else{
                output = interval / 3;
            }
        }
    }
    // テキストを外部ファイルでやる
}

int card_dict(int key_input, int num){ // 辞書型っぽいやつの関数
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
    return (value[index] - num);
}

void card_shaffule(int card_list[], int size){ // 山札をシャッフル
    srand((unsigned int)time(NULL));

    for(int i = size - 1; i > 0; i--){
        int j = rand() % (i + 1);

        int tmp = card_list[i];
        card_list[i] = card_list[j];
        card_list[j] = tmp;
    }
}

void generate_list(int card_list[]){ // シャッフルされていない山札を生成
    for(int i = 0; i < CARDS; i++){
        int num = 0;
        int j = 0;
        for(j; j < value[i]; j++){
            card_list[num + j] = key[i];
        }
        num += j;
    }
}

int calc_sum(int card[], int size){ // カードの合計を計算する関数
    int sum = 0;
    int max = card[0];
    int max_flag = 0;
    int double_flag = 0;
    int shuffle_flag = 0;
    for(int i = 0; i < size; i++){
        switch (card[i]){
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
            if(card[i] > max){ // カードの最大値を保存
                max = card[i];
            }
            sum += card[i];
            break;
        }
    }
    if(max_flag){ // フラグが立っていればMAXを消去
        sum -= max;
    }
    if(double_flag){ // フラグが立っていれば二倍
        sum = 2 * sum;
    }
    return sum;
}

int play_main(player *p){
    srand((unsigned int)time(NULL));
    int num = 0;

    for(int i = 0; i < CARDS; i++){ // 山札の枚数をnumに代入
        num += value[i];
    }
    int card_list[num];
    generate_list(card_list); // 山札を生成
    card_shaffule(card_list, num); // 山札をシャッフル
    int start = (rand() % Players); // スタートプレイヤーをランダムに決定
    int turn = 0; // 山札を引く回数を保存するための変数

    while(p[0]->life && p[1]->life && p[2]->life && p[3]->life){ 
        // コヨーテしたらここに戻る
        int playcard[Players]; // プレイヤーの持つカードを保存
        int flag;
        
        for(int i = 0; i < Players; i++){ 
            // 適宜文字を変更しながらプレイヤーの手札を決定、構造体に代入
            switch (card_list[(turn * Players) + i]){
                case 100:
                    p[i].card = "MAX->0";
                    break;
                case 200:
                    p[i].card = "x2";
                    break;
                case 199:
                    p[i].card = "シャッフル0";
                    flag = 1; // シャッフルフラグ
                    break;
                default:
                char str[20];
                    sprintf(str, "%d", card_list[(turn * Players) + i]);
                    // 上記に合わせてintをcharに
                    p[i].card = str;
                    break;
            }
            playcard[i] = card_list[(turn * Players) + i];
        }

        int prevnum = 0; // 直前に宣言した数を保存
        int card_sum = calc_sum(playcard, Players); // 場の合計を計算
        while(1){ // プレイのためのループ
            int i = 0; // プレイヤーの試行ターンを保存
            int dec; // プレイヤーの行動を保存
            int play_turn = (start + i) % Players; // 誰のターンか計算
            if(play_turn == Players - 1){ // 3ならお前の番
                dec = Player_Move(*p, prevnum);
            }
            else{
                dec = Ai_Move(*p, prevnum, play_turn);
            }
            if(dec == -1){ // コヨーテ後の処理
                printf("プレイヤー%dによりコヨーテが宣言されました。\n", play_turn + 1);
                printf("場のカードは");
                for(int j = 0; j < Players; j++){ // 場のカード全出力
                    printf("プレイヤー%d:%s ", j + 1, p[j]->card);
                }
                printf("です。\n合計値は%dでした。", card_sum);
                if(prevnum > card_sum){ // 宣言されていた数がデカいと…
                    start = (play_turn - 1) % Players;
                    printf("コヨーテ成功です。プレイヤー%dのライフが一つ減ります。", (start) + 1);
                    p[start]->life -= 1;
                }
                else{ // 小さいと…
                    start = play_turn;
                    printf("コヨーテ失敗です。プレイヤー%dのライフが一つ減ります。", play_turn + 1);
                    p[play_turn]->life -= 1;
                }
                if(flag){ // シャッフルフラグが立っている場合
                    generate_list(card_list);
                    card_shaffule(card_list, num);

                    turn = 0; // 山札を引く場所もリセット
                    value_copy = value; // valueもリセット
                }
                else{
                    turn += 1; // 山札を次のゾーンへ
                }
                break;
            }
            else{
                i += 1;
            }
        }
    }
    int lose;
    for(int i = 0; i < Players; i++){
        if(p[i]->life == 0){
            lose = i;
        }
    }
    if(lose == 3){
        printf("ゲーム終了 あなたの負けです。");
    }
    else{
        printf("ゲーム終了 プレイヤー%dの負けです。", lose);
    }
}

int main(void){
    player p[Players];
    p[0]->life = 2;
    p[1]->life = 2;
    p[2]->life = 2;
    p[3]->life = 2;

}