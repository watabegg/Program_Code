#include <stdio.h>

#define LIMIT_LOW 0
#define LIMIT_HIGH 25

int main(void) {
  int temp;
  int max = LIMIT_LOW;
  int min = LIMIT_HIGH;

  scanf("%d", &temp);
  while ( (LIMIT_LOW <= temp) && (temp <= LIMIT_HIGH)) {
    if(temp > max){
        max = temp;
    }
    if(temp < min){
        min = temp;
    }
    scanf("%d", &temp);
  }


  printf("MAX = %d\n", max) ;
  printf("MIN = %d\n", min) ;
  
  return 0 ;
}