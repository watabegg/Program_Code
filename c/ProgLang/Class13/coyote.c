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

int calc_sum(int card[], int size){ // カードの合計を計算する関数
    int sum = 0;
    int max = -10;
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

int Player_Move(player *p, int prev){ // playerのデータを受け付けて行動決定
    printf("現在のプレイヤーの手札は\n");
    for(int i = 0; i < Players - 1; i++){
        printf("プレイヤー%d:%s ", i + 1, p[i].card);
    }
    printf("\nです。\n\n");
    if(prev != 0){
        printf("直前のプレイヤーは%dを宣言しています。\n", prev);
    }
    else{
        printf("あなたが最初のプレイヤーです。\n");
    }
    int input;
    char input_str[100];
    char str[2];
    int flag = 0;

    while(1){
        if(prev != 0){
            printf("コヨーテを宣言しますか？(はい:y いいえ:n):");
            scanf("%s", &str);
            if(strcmp(str, "y") == 0){
                flag = 1;
                break;
            }
            else if(strcmp(str, "n") == 0){
                break;
            }
            else{
                printf("入力エラー yかnを入力してください。\n");
            }
        }
        else{
            break;
        }
    }
    if(flag == 1){
        printf("あなたはコヨーテを宣言しました。\n\n");
        input = -1;
    }
    else{
        while(1){
            printf("宣言する数字を入力してください:");
            fgets(input_str, sizeof(input_str), stdin);

            char *endptr;
            input = strtol(input_str, &endptr, 10);

            if(input_str[0] != '\n' && *endptr == '\n' && *endptr != '\0' && input != 0 && input > prev){
                break;
            }
            else{
                printf("入力エラー 数値以外、もしくは前の宣言より小さい数字が入力されています。\n");
            }
        }
        printf("あなたは%dを宣言しました。\n", input);
    }

    return input;
}

int Ai_Move(int card[], int prev, int turn){
    int otherhand[Players] = {0}; // 他プレイヤーの手札
    int guess = 5; // botの手札予想
    int *pguess = &guess; // guessのポインタ
    static int self_prev[Players - 1] = {0}; // 自分の直前の宣言
    int max_flag = 0; // MAX->0フラグ
    int double_flag = 0; // x2フラグ
    int output; // botの行動返り値
    for(int i = 0; i < Players; i++){
        if(i != turn){
            otherhand[i] = card[i];
            switch (card[i]){
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
    otherhand[turn] = guess;
    int sum = calc_sum(otherhand, Players);
    if(prev == 0){
        if(sum < 0){
            output = 1;
        }
        else{
            output = (sum / 3) + 1;
        }
    }
    else{
        int interval = prev - self_prev[turn];
        if(prev > sum){
            if(interval > 3 && interval <= 6){
                *pguess = 10;
                sum = calc_sum(otherhand, Players);
                if(prev >= sum){
                    output = -1; // コヨーテ
                }
                else{
                    output = 1; // +1宣言
                }
            }
            else if(interval > 6){
                *pguess = 200; // x2と予想
                sum = calc_sum(otherhand, Players);
                if(double_flag){ // x2フラグがなかったら
                    if(prev >= sum){
                        output = -1; // コヨーテ
                    }
                    else{
                        output = 2;
                    }
                }
                else{
                    output = 1;
                }
                
            }
            else if(interval == 3){
                output = 1;
            }
            else{
                output = 1;
            }
        }
        else{
            if(interval == 3){
                output = 1;
            }
            else if(interval > 3 && interval <= 9){
                *pguess = 0;
                sum = calc_sum(otherhand, Players);
                if(prev >= sum){
                    output = 1;
                }
                else{
                    output = 2;
                }
            }
            else{
                output = (interval / 3) + 1;
            }
        }
    }
    if(output != -1){
        output += prev;
    }

    return output;
    // フレーバーテキストを外部ファイルでやる
}

int card_shaffule(int card_list[], int size){ // 山札をシャッフル
    srand((unsigned int)time(NULL));

    for(int i = size - 1; i > 0; i--){
        int j = rand() % (i + 1);

        int tmp = card_list[i];
        card_list[i] = card_list[j];
        card_list[j] = tmp;
    }

    return 0;
}

int generate_list(int card_list[]){ // シャッフルされていない山札を生成
int num = 0;
    for(int i = 0; i < CARDS; i++){
        int j = 0;
        for(j; j < value[i]; j++){
            card_list[num + j] = key[i];
        }
        num += j;
    }

    return 0;
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

    while(p[0].life && p[1].life && p[2].life && p[3].life){ 
        // コヨーテしたらここに戻る
        int playcard[Players]; // プレイヤーの持つカードを保存
        int flag;
        
        for(int i = 0; i < Players; i++){ 
            char str[20];
            // 適宜文字を変更しながらプレイヤーの手札を決定、構造体に代入
            switch (card_list[(turn * Players) + i]){
                case 100:
                    strcpy(p[i].card, "MAX->0");
                    break;
                case 200:
                    strcpy(p[i].card, "x2");
                    break;
                case 199:
                    strcpy(p[i].card, "シャッフル0");
                    flag = 1; // シャッフルフラグ
                    break;
                default:
                    sprintf(str, "%d", card_list[(turn * Players) + i]);
                    // 上記に合わせてintをcharに
                    strcpy(p[i].card, str);
                    break;
            }
            playcard[i] = card_list[(turn * Players) + i];
        }

        int prevnum = 0; // 直前に宣言した数を保存
        int i = 0; // プレイヤーの試行ターンを保存
        int card_sum = calc_sum(playcard, Players); // 場の合計を計算
        while(1){ // プレイのためのループ
            int dec = 0; // プレイヤーの行動を保存
            int play_turn = (start + i) % Players; // 誰のターンか計算
            if(play_turn == Players - 1){ // 3ならお前の番
                dec = Player_Move(p, prevnum);
            }
            else{
                dec = Ai_Move(playcard, prevnum, play_turn);
                if(dec != -1){
                    printf("プレイヤー%dは%dを宣言しました。\n", play_turn + 1, dec);
                }
            }
            if(dec == -1){ // コヨーテ後の処理
                printf("プレイヤー%dによりコヨーテが宣言されました。\n", play_turn + 1);
                printf("場のカードは");
                for(int j = 0; j < Players; j++){ // 場のカード全出力
                    printf("プレイヤー%d:%s ", j + 1, p[j].card);
                }
                printf("です。\n合計値は%dでした。\n\n", card_sum);
                if(prevnum > card_sum){ // 宣言されていた数がデカいと…
                    start = (play_turn + 3) % Players;
                    printf("コヨーテ成功です。プレイヤー%dのライフが一つ減ります。\n", (start) + 1);
                    p[start].life -= 1;
                }
                else{ // 小さいと…
                    start = play_turn;
                    printf("コヨーテ失敗です。プレイヤー%dのライフが一つ減ります。\n", play_turn + 1);
                    p[play_turn].life -= 1;
                }
                if(flag){ // シャッフルフラグが立っている場合
                    generate_list(card_list);
                    card_shaffule(card_list, num);

                    turn = 0; // 山札を引く場所もリセット
                }
                else{
                    turn += 1; // 山札を次のゾーンへ
                }
                break;
            }
            else{
                i += 1;
                prevnum = dec;
            }
        }

    }
    int lose;
    for(int i = 0; i < Players; i++){
        if(p[i].life == 0){
            lose = i;
        }
    }
    if(lose == 3){
        printf("ゲーム終了 あなたの負けです。");
    }
    else{
        printf("ゲーム終了 プレイヤー%dの負けです。", lose + 1);
    }

    return 0;
}

int main(void){
    player p[Players];

    p[0].life = 2;
    p[1].life = 2;
    p[2].life = 2;
    p[3].life = 2;

    play_main(p);
}