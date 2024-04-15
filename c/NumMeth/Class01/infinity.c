#include<stdio.h>

int main(){
    double a, b;
    a = 1.0 / 0.0;

    printf("a=%f \n", a);
    b = 1.0 / a;
    printf("b=%f \n", b);

    return 0;
}