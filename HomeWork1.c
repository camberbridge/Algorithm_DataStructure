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
void polish(char str[], char r_polish[], char R_polish[], int *len);  /*逆ポーランド記法への変換*/
void code(char R_polish[]);  /*中間コードへの変換*/

int main(void){
  char str[BUFLEN];  /*コマンドラインからの入力の格納用*/
  char r_polish[BUFLEN];  /*逆ポーランド記法コードの格納用*/
  char R_polish[BUFLEN];  /*逆ポーランド記法コードの格納用(解)*/
  int len; /*逆ポーランド文字列の長さを格納*/

  fgets(str, BUFLEN, stdin);  /*コマンドライン引数を制限80文字でstr[]に格納*/
  polish(str, r_polish, R_polish, &len);

  printf("Reverse Polish notation ... %s\n", R_polish);  /*逆ポーランド記法コードの出力*/
  printf("length=%d\n", len);  /*逆ポーランド記法の長さの出力*/
  printf("Intermediate Code\n");
  code(R_polish);  /*中間コード処理*/

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

void polish(char str[], char r_polish[], char R_polish[], int *len){
  int i = 0, j = 0;
  for(i = 0; i < strlen(str); i++){
    if(charac(str[i]) == 1){  /*変数だったらそのまま出力*/
      r_polish[x] = str[i];
      ++x;
      continue;
    }else if(charac(str[i]) == 2){  /*演算子だったら以下の条件分岐にかける*/
      if((str[i] == '+') || (str[i] == '-')){  /*'+', '-'だったら*/
        while((STACK[StkCtr - 1] == '*') || (STACK[StkCtr - 1] == '/') || (STACK[StkCtr - 1] == '+') || (STACK[StkCtr - 1] == '-')){  /*スタックの先頭が'*', '/', '+', '-'だったらスタックの先頭をpop*/
          pop(&r_polish[x]);
          ++x;
        }
        push(&str[i]);  /*スタックに積む*/
        continue;
      }else if((str[i] == '*') || (str[i] == '/')){  /*'*', '/'だったら*/
        while((STACK[StkCtr - 1] == '*') || (STACK[StkCtr - 1] == '/')){  /*スタックの先頭が'*', '/'だったらスタックの先頭をpop*/
          pop(&r_polish[x]);
          ++x;
        }
        push(&str[i]);  /*スタックに積む*/
        continue;
      }else if(str[i] == '('){  /*'('だったらpush*/
        push(&str[i]);
        continue;
      }else if(str[i] == ')'){  /*')'だったらスタックの先頭が'('になるまでpop. そして'('は出力しない*/
        while(1){
          if(STACK[StkCtr - 1] == '('){
            char parentheses[BUFLEN]; /*左括弧格納用*/
            pop(&parentheses[j]);
            ++j;
            break;  /*左括弧を検出したらループ脱出*/
          }else if(STACK[StkCtr - 1] != '('){
            pop(&r_polish[x]);
            ++x;
          }
        }
        continue;
      }
    }else if(charac(str[i]) == 0){  /*入力が終了したらスタックの先頭から順にpop*/
      while(StkCtr != 0){
        pop(&r_polish[x]);
        ++x;
      }
      break;
    }
  }
  
  *len = x;  /*r_polishの文字列長更新*/

  /*コンパイラによっては算術表現を変換にかけると全処理終了後の逆ポーランド文字列の末尾に化けた文字が余計に追加される場合が時々あるので、それを切り離す。*/
  for(i = 0; i < x; i++){
    R_polish[i] = r_polish[i]; /*逆ポーランド文字列の解はR_polishへ*/
  }
}

void code(char R_polish[]){
  StkCtr = 0;
  char trashlist[BUFLEN]; /*ゴミ入れ*/
  char tmp[BUFLEN];
  int opecount = 0, transcount = 0;
  int i = 0, j = 0;

  for(i = 0; i < x; i++){  /*逆ポーランド文字列には演算子がいくつあるか*/
   if((charac(R_polish[i])) == 2){
      opecount++;
   }
  }
  
  for(i = 0; i < x; i++){
    if((charac(R_polish[i])) == 1){  /*変数ならスタックに積む*/
      push(&R_polish[i]);
    }else if((charac(R_polish[i])) == 2){  /*演算子なら以下の条件分岐にかける*/
      transcount++;
      sprintf(tmp, "%d", transcount);  /*int -> char 変換*/
      if(transcount == 1){
        printf("T%s <- %c %c %c\n", tmp, STACK[StkCtr - 2], R_polish[i], STACK[StkCtr - 1]);
      }
      if(transcount >= 2){
        if(((charac(STACK[StkCtr - 1])) != 0) && ((charac(STACK[StkCtr - 2])) != 0)){
          printf("T%s <- %c %c %c\n", tmp, STACK[StkCtr - 2], R_polish[i], STACK[StkCtr - 1]);
        }else if(((charac(STACK[StkCtr - 1])) == 0) && ((charac(STACK[StkCtr - 2])) == 0)){
          printf("T%s <- T%c %c T%c\n", tmp, STACK[StkCtr - 2], R_polish[i], STACK[StkCtr - 1]);
        }else if((charac(STACK[StkCtr - 1])) == 0){
          printf("T%s <- %c %c T%c\n", tmp, STACK[StkCtr - 2], R_polish[i], STACK[StkCtr - 1]);
        }else if((charac(STACK[StkCtr - 2])) == 0){
          printf("T%s <- T%c %c %c\n", tmp, STACK[StkCtr - 2], R_polish[i], STACK[StkCtr - 1]);
        }
      }

      /*スタックの先頭から2つの要素をゴミ箱へ*/
      pop(&trashlist[j]);
      pop(&trashlist[j]);
      j = j  + 2;

      push(tmp);  /*T? をスタックに積む*/

      /*演算子の数だけ処理を行ったら中間コード処理終了*/
      if(transcount == opecount){
        break;
      }
    }
  }
}
