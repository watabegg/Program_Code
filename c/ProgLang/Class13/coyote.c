#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Players 4
#define CARDS 14
#define MAX_LENGTH 256
#define MAX_LINES 15

int key[CARDS] = {0,1,2,3,4,5,10,15,20,-5,-10,200,100,199}; // 200:x2 100:MAX0 199:s0
int value[CARDS] = {3,4,4,4,4,4,3,2,1,2,1,1,1,1}; // 各カードの枚数を保存するリスト

typedef struct { // プレイヤーのための構造体
    int life;
    char card[20];
} player;

void delay(int milliseconds) { // 遅延のための関数,botの思考時間を追加
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

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
            fflush(stdin); // 標準出力バッファをクリア

            printf("宣言する数字を入力してください:");
            fgets(input_str, sizeof(input_str), stdin);

            // 改行文字を取り除く
            size_t len = strlen(input_str);
            if (len > 0 && input_str[len - 1] == '\n') {
                input_str[len - 1] = '\0';
                len--;  // 改行文字を含まない長さに変更
            }

            char *endptr;
            input = strtol(input_str, &endptr, 10);

            if(len > 0 && input > prev){
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

int Ai_Move(int card[], int prev, int turn, char msg[][MAX_LENGTH]){
    int otherhand[Players] = {0}; // 他プレイヤーの手札
    int guess = 5; // botの手札予想
    int *pguess = &guess; // guessのポインタ
    static int self_prev[Players - 1] = {0}; // 自分の直前の宣言
    int max_flag = 0; // MAX->0フラグ
    int double_flag = 0; // x2フラグ
    int min_flag = 0; // -10フラグ
    int twenty_flag = 0; // 20フラグ
    int output = 0; // botの行動返り値
    int msg_num = 0;

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
                case -10:
                    min_flag = 1;
                case 20:
                    twenty_flag = 1;
                default:
                    break;
            }
        }
    }
    otherhand[turn] = guess;
    int sum = calc_sum(otherhand, Players); // 予想合計値を計算
    if(prev == 0){ // 直前に何も宣言されていない(スタートプレイヤー)
        if(sum < 0){ // 予想合計値が0より小さい
            msg_num = 0;
            output = 1;
        }
        else{ 
            msg_num = 1;
            output = (sum / 3) + 1; // 予想合計値の1/3を宣言
        }
    }
    else{
        int interval = prev - self_prev[turn]; // 直前の宣言から直前の自分の宣言を引いたものが宣言の飛ばし具合
        if(prev > sum){ // 予想合計より直前宣言の方が大きい
        // この場合はguessが大きいかコヨーテチャンス
            if(interval > 3 && interval <= 6){ // 1プレイヤー平均2宣言
                printf("プレイヤー%d:%s\n", turn + 1, msg[2]);
                *pguess = 10; // 予想を10に変更
                sum = calc_sum(otherhand, Players);
                if(prev >= sum){ 
                    msg_num = 14;
                    output = -1; // コヨーテ
                }
                else{
                    msg_num = 8;
                    output = 1; // +1宣言
                }
            }
            else if(interval > 6){ // 1プレイヤー平均2以上の宣言
                printf("プレイヤー%d:%s\n", turn + 1, msg[2]);
                if(double_flag == 0){ // x2フラグがない
                    *pguess = 200; // x2と予想
                }
                else if(twenty_flag == 0){ // 20フラグがない
                    *pguess = 20; 
                }
                else{ // フラグがない(雑処理だけど)
                    *pguess = 10;
                }
                sum = calc_sum(otherhand, Players);
                if(prev >= sum){ // 予想合計より直前宣言の方が大きい
                    msg_num = 14;
                    output = -1; // コヨーテ
                }
                else{
                    msg_num = 4;
                    output = 2; // 2宣言
                }
                
            }
            else if(interval == 3){ // 1プレイヤー1のみの宣言
                msg_num = 13;
                output = -1; // コヨーテ
            }
            else{ // 例外処理
                msg_num = 11;
                output = 1; 
            }
        }
        else{ // 予想合計のほうが大きい
        // この場合はguessが小さいか序盤
            if(interval == 3){ // 1プレイヤー1のみの宣言
                if(self_prev[turn] == 0){ // 序盤
                    msg_num = 7;
                    output = 1; 
                }
                else{ // 序盤ではないのでguessを更新して条件分岐
                    printf("プレイヤー%d:%s\n", turn + 1, msg[6]);
                    if(min_flag == 0){ // -10フラグがない
                        *pguess = -10;
                    }
                    else if(max_flag == 0){ // max0フラグがない
                        *pguess = 100;
                    }
                    else{ // フラグが立っていない(雑処理)
                        *pguess = 3;
                    }
                    sum = calc_sum(otherhand, Players);
                    if(prev >= sum){ // 更新した予想合計より直前宣言の方が大きい
                        msg_num = 14;
                        output = -1;
                    }
                    else{
                        msg_num = 9;
                        output = 1; // 小さいならわからないので1宣言
                    }
                }
            }
            else if(interval > 3 && interval <= 9){ // 1プレイヤー平均1~3程度の宣言
                // 序盤な気がする
                *pguess = 0;
                sum = calc_sum(otherhand, Players);
                if(prev >= sum){
                    msg_num = 10;
                    output = 1;
                }
                else{
                    msg_num = 4;
                    output = 2;
                }
            }
            else{ // 例外処理
                msg_num = 11;
                output = 1;
            }
        }
    }
    
    if(output != -1){
        output = prev + output;
        self_prev[turn] = output;
    }
    printf("プレイヤー%d:%s\n", turn + 1, msg[msg_num]);
    delay(500);

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
    const char *filename = "flavor_text.txt";

    // ファイルのオープン
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "ファイル %s を開くのに失敗しました。\n", filename);
        return 1;
    }

    // 行ごとの文字列を格納する配列
    char lines[MAX_LINES][MAX_LENGTH];

    // 行ごとに読み込んで配列に格納
    int line_count = 0;
    while (line_count < MAX_LINES && fgets(lines[line_count], MAX_LENGTH, file) != NULL) {
        // 行末の改行文字を削除
        int len = strlen(lines[line_count]);
        if (len > 0 && lines[line_count][len - 1] == '\n') {
            lines[line_count][len - 1] = '\0';
        }

        line_count++;
    }

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
        printf("ゲームスタートです。\n\n");
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
                dec = Ai_Move(playcard, prevnum, play_turn, lines);
                if(dec != -1){
                    printf("プレイヤー%dは%dを宣言しました。\n\n", play_turn + 1, dec);
                }
            }
            if(dec == -1){ // コヨーテ後の処理
                printf("プレイヤー%dによりコヨーテが宣言されました。\n\n", play_turn + 1);
                printf("場のカードは");
                for(int j = 0; j < Players; j++){ // 場のカード全出力
                    printf("プレイヤー%d:%s ", j + 1, p[j].card);
                }
                printf("です。\n合計値は%dでした。\n\n", card_sum);
                if(prevnum > card_sum){ // 宣言されていた数がデカいと…
                    start = (play_turn + 3) % Players;
                    printf("コヨーテ成功です。プレイヤー%dのライフが一つ減ります。\n\n", (start) + 1);
                    p[start].life -= 1;
                }
                else{ // 小さいと…
                    start = play_turn;
                    printf("コヨーテ失敗です。プレイヤー%dのライフが一つ減ります。\n\n", play_turn + 1);
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