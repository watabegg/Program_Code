#include <stdio.h>
#define NAMELEN 10

/* 構造体の定義 */
typedef struct personal_t {
  int age;      /* 年齢 */
  char *name;  /* 名前 */
} person;       /* 個人データ */


int main(void) {
  /* 名前データを別に用意 */
  char nameData[NAMELEN] = "Kanda";
 
  /* 構造体 person 型の変数の宣言と初期化 */
  person p1 = {30, nameData};
  person p2;
 
  p2 = p1;
  p1.name[0] = 'P';

  /* 各メンバの値を表示する */
  printf("age: %d\n", p2.age);
  printf("name: %s\n", p2.name);

  return 0;
}