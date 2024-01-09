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

int calc_sum(int card[], int size){ // �J�[�h�̍��v���v�Z����֐�
    int sum = 0;
    int max = -10;
    int max_flag = 0;
    int double_flag = 0;
    int shuffle_flag = 0;
    for(int i = 0; i < size; i++){
        switch (card[i]){
        case 200: // x2�̃J�[�h����ɂ���ꍇ
            double_flag = 1;
            break;
        case 100: // MAX0�̃J�[�h����ɂ���ꍇ
            max_flag = 1;
            break;
        case 199: // �V���b�t��0�̃J�[�h����ɂ���ꍇ
            shuffle_flag = 1;
            break;
        default:
            if(card[i] > max){ // �J�[�h�̍ő�l��ۑ�
                max = card[i];
            }
            sum += card[i];
            break;
        }
    }
    if(max_flag){ // �t���O�������Ă����MAX������
        sum -= max;
    }
    if(double_flag){ // �t���O�������Ă���Γ�{
        sum = 2 * sum;
    }
    return sum;
}

int Player_Move(player *p, int prev){ // player�̃f�[�^���󂯕t���čs������
    printf("���݂̃v���C���[�̎�D��\n");
    for(int i = 0; i < Players - 1; i++){
        printf("�v���C���[%d:%s ", i + 1, p[i].card);
    }
    printf("\n�ł��B\n\n");
    if(prev != 0){
        printf("���O�̃v���C���[��%d��錾���Ă��܂��B\n", prev);
    }
    else{
        printf("���Ȃ����ŏ��̃v���C���[�ł��B\n");
    }
    int input;
    char input_str[100];
    char str[2];
    int flag = 0;

    while(1){
        if(prev != 0){
            printf("�R���[�e��錾���܂����H(�͂�:y ������:n):");
            scanf("%s", &str);
            if(strcmp(str, "y") == 0){
                flag = 1;
                break;
            }
            else if(strcmp(str, "n") == 0){
                break;
            }
            else{
                printf("���̓G���[ y��n����͂��Ă��������B\n");
            }
        }
        else{
            break;
        }
    }
    if(flag == 1){
        printf("���Ȃ��̓R���[�e��錾���܂����B\n\n");
        input = -1;
    }
    else{
        while(1){
            printf("�錾���鐔������͂��Ă�������:");
            fgets(input_str, sizeof(input_str), stdin);

            char *endptr;
            input = strtol(input_str, &endptr, 10);

            if(input_str[0] != '\n' && *endptr == '\n' && *endptr != '\0' && input != 0 && input > prev){
                break;
            }
            else{
                printf("���̓G���[ ���l�ȊO�A�������͑O�̐錾��菬�������������͂���Ă��܂��B\n");
            }
        }
        printf("���Ȃ���%d��錾���܂����B\n", input);
    }

    return input;
}

int Ai_Move(int card[], int prev, int turn){
    int otherhand[Players] = {0}; // ���v���C���[�̎�D
    int guess = 5; // bot�̎�D�\�z
    int *pguess = &guess; // guess�̃|�C���^
    static int self_prev[Players - 1] = {0}; // �����̒��O�̐錾
    int max_flag = 0; // MAX->0�t���O
    int double_flag = 0; // x2�t���O
    int output; // bot�̍s���Ԃ�l
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
                    output = -1; // �R���[�e
                }
                else{
                    output = 1; // +1�錾
                }
            }
            else if(interval > 6){
                *pguess = 200; // x2�Ɨ\�z
                sum = calc_sum(otherhand, Players);
                if(double_flag){ // x2�t���O���Ȃ�������
                    if(prev >= sum){
                        output = -1; // �R���[�e
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
    // �t���[�o�[�e�L�X�g���O���t�@�C���ł��
}

int card_shaffule(int card_list[], int size){ // �R�D���V���b�t��
    srand((unsigned int)time(NULL));

    for(int i = size - 1; i > 0; i--){
        int j = rand() % (i + 1);

        int tmp = card_list[i];
        card_list[i] = card_list[j];
        card_list[j] = tmp;
    }

    return 0;
}

int generate_list(int card_list[]){ // �V���b�t������Ă��Ȃ��R�D�𐶐�
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

    for(int i = 0; i < CARDS; i++){ // �R�D�̖�����num�ɑ��
        num += value[i];
    }
    int card_list[num];
    generate_list(card_list); // �R�D�𐶐�
    card_shaffule(card_list, num); // �R�D���V���b�t��
    int start = (rand() % Players); // �X�^�[�g�v���C���[�������_���Ɍ���
    int turn = 0; // �R�D�������񐔂�ۑ����邽�߂̕ϐ�

    while(p[0].life && p[1].life && p[2].life && p[3].life){ 
        // �R���[�e�����炱���ɖ߂�
        int playcard[Players]; // �v���C���[�̎��J�[�h��ۑ�
        int flag;
        
        for(int i = 0; i < Players; i++){ 
            char str[20];
            // �K�X������ύX���Ȃ���v���C���[�̎�D������A�\���̂ɑ��
            switch (card_list[(turn * Players) + i]){
                case 100:
                    strcpy(p[i].card, "MAX->0");
                    break;
                case 200:
                    strcpy(p[i].card, "x2");
                    break;
                case 199:
                    strcpy(p[i].card, "�V���b�t��0");
                    flag = 1; // �V���b�t���t���O
                    break;
                default:
                    sprintf(str, "%d", card_list[(turn * Players) + i]);
                    // ��L�ɍ��킹��int��char��
                    strcpy(p[i].card, str);
                    break;
            }
            playcard[i] = card_list[(turn * Players) + i];
        }

        int prevnum = 0; // ���O�ɐ錾��������ۑ�
        int i = 0; // �v���C���[�̎��s�^�[����ۑ�
        int card_sum = calc_sum(playcard, Players); // ��̍��v���v�Z
        while(1){ // �v���C�̂��߂̃��[�v
            int dec = 0; // �v���C���[�̍s����ۑ�
            int play_turn = (start + i) % Players; // �N�̃^�[�����v�Z
            if(play_turn == Players - 1){ // 3�Ȃ炨�O�̔�
                dec = Player_Move(p, prevnum);
            }
            else{
                dec = Ai_Move(playcard, prevnum, play_turn);
                if(dec != -1){
                    printf("�v���C���[%d��%d��錾���܂����B\n", play_turn + 1, dec);
                }
            }
            if(dec == -1){ // �R���[�e��̏���
                printf("�v���C���[%d�ɂ��R���[�e���錾����܂����B\n", play_turn + 1);
                printf("��̃J�[�h��");
                for(int j = 0; j < Players; j++){ // ��̃J�[�h�S�o��
                    printf("�v���C���[%d:%s ", j + 1, p[j].card);
                }
                printf("�ł��B\n���v�l��%d�ł����B\n\n", card_sum);
                if(prevnum > card_sum){ // �錾����Ă��������f�J���Ɓc
                    start = (play_turn + 3) % Players;
                    printf("�R���[�e�����ł��B�v���C���[%d�̃��C�t�������܂��B\n", (start) + 1);
                    p[start].life -= 1;
                }
                else{ // �������Ɓc
                    start = play_turn;
                    printf("�R���[�e���s�ł��B�v���C���[%d�̃��C�t�������܂��B\n", play_turn + 1);
                    p[play_turn].life -= 1;
                }
                if(flag){ // �V���b�t���t���O�������Ă���ꍇ
                    generate_list(card_list);
                    card_shaffule(card_list, num);

                    turn = 0; // �R�D�������ꏊ�����Z�b�g
                }
                else{
                    turn += 1; // �R�D�����̃]�[����
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
        printf("�Q�[���I�� ���Ȃ��̕����ł��B");
    }
    else{
        printf("�Q�[���I�� �v���C���[%d�̕����ł��B", lose + 1);
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