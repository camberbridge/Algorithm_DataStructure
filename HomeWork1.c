#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 80
#define STKLMT 100
char STACK[STKLMT];
int StkCtr;
int x;  /*r_polishの要素位置*/

void push(char *c);  /*スタックにcを積む*/
void pop(char *c);  /*スタックの先頭の要素をcに返す*/
int charc(char c);  /*cが変数(a,.., z)なら1, 演算子(+, -, *, /, (, ))なら2, その他なら0 を返す*/
void polish(char str[], char r_polish[]);  /*逆ポーランド記法への変換*/
//void code(char r_polish[]);  /*中間コードへの変換*/

int main(void){
  char str[BUFLEN];  /*コマンドラインからの入力の格納用*/
  char r_polish[BUFLEN];  /*逆ポーランド記法コードの格納用*/

  fgets(str, BUFLEN, stdin);  /*コマンドライン引数を制限80文字でstr[]に格納*/
  polish(str, r_polish);

  printf("Reverse Polish notation ... %s\n", r_polish);  /*逆ポーランド記法コードの出力*/
  printf("length=%lu\n", strlen(r_polish));  /*逆ポーランド記法の長さの出力*/
  printf("Intermediate Code\n");
//  code(r_polish);  /*中間コード処理*/

  return 0;
}

void push(char *c){
  if(StkCtr >= STKLMT){  /*スタックの制限100を超えたらexit*/
    printf("Error-- STACK Empty\n");
    exit(1); 
  }
  
  STACK[StkCtr] = *c;
  StkCtr++;
}

void pop(char *c){
  if(StkCtr <=  0){  /*スタックが空ならexit*/
    printf("Error-- STACK Empty\n");
    exit(1);
  }

  StkCtr--;
  *c = STACK[StkCtr];
}

int charac(char c){
  char variable[26] = {"abcdefghijklmnopqrstuvwxyz"}, oper[6] = {"+-*/()"};
  int i = 0;

  for(i = 0; i < 26; i++){
    if(c == variable[i]) return 1;
  }
  for(i = 0; i < 6; i++){
    if(c == oper[i]) return 2;
  }

  return 0;
}

void polish(char str[], char r_polish[]){
  char c;
  int i = 0, j = 0;
  for(i = 0; i < strlen(str); i++){
    if(charac(str[i]) == 1){  /*変数だったらそのまま出力*/
      r_polish[x] = str[i];
      ++x;
      continue;
    }else if(charac(str[i]) == 2){  /*演算子だったら以下の条件分岐にかける*/
      if((str[i] == '+') || (str[i] == '-')){  /*'+', '-'だったら*/
        while((STACK[StkCtr] == '*') || (STACK[StkCtr] == '/')){  /*スタックの先頭が'*', '/'だったらスタックの先頭をpop*/
          pop(&r_polish[x]);
          ++x;
        }
        push(&str[i]);  /*スタックに積む*/
        continue;
      }else if((str[i] == '*') || str[i] == '/'){  /*'*', '/'だったら*/
        push(&str[i]);  /*スタックに積む*/
        continue;
      }
    }else if(str[i] == '('){  /*'('だったらpush*/
      push(&str[i]);
      continue;
    }else if(str[i] == ')'){  /*')'だったらスタックの先頭が'('になるまでpop. そして'('は出力しない*/
      while(STACK[StkCtr] != '('){
        pop(&r_polish[x]);
        ++x;
      }
      --StkCtr;
      continue;
    }else if(charac(str[i]) == 0){  /*入力が終了したらスタックの先頭から順にpop*/
      while(StkCtr != 0){
        pop(&r_polish[x]);
        ++x;
      }
      break;
    }
  }
  printf("------------%d\n", x);
}

//void code(char r_polish[]){
//
//}
