#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define COUNT_MAX 10 //���͉񐔐���

int main(void) {
    srand((unsigned int)time(NULL));
    int ans = rand() % 1000;
    int res;
    int count;

    printf("0~999�̐����𓖂Ă悤�I�I\n\n");

    do {
        printf("�������ȁF");
        scanf("%d", &res);

        if (res > ans){ //���͂��������傫���Ƃ�
            printf("�傫�����܂�\n");
        }
        else if (res < ans){ //���͂��������傫���Ƃ�
            printf("���������܂�\n");
        }
        count += 1;
        if(count >= COUNT_MAX){ //�񐔒�������while�E�o
            break;
        }

    } while (res != ans);

    if(count >= COUNT_MAX){
        printf("�񐔐����𒴂��܂����I������%d�ł����B\n", ans);
    }
    else{
        printf("�����ł��I������%d�ł���\n", ans);
    }

    return 0 ;
}