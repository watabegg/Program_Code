#include <stdio.h>

int main(void){
    int i;
    int* pi;

    pi = &i;
    *pi = 10;

    printf("i=%d\n", &i);
    printf("pi=%p\n", &pi);
    printf("&i=%d\n", *(&i));
    printf("*pi=%p\n", *(&pi));
}