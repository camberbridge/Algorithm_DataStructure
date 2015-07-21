#include <stdio.h>
#define N 8
//int Merge[N] = {92, 69, 1, 50, 9, 92, 42, 1}, tmpmerge[N];
int Merge[N] = {92, 69, 56, 50, 9, 33, 42, 1}, tmpmerge[N];

void printdata(int data[]);  /*ソートの途中経過や結果の出力*/
void mergesort(int first, int last);
void merge_two(int fr1, int to1, int fr2, int to2);


int main(void){
  /*乱数を発生させ、Merge[]に格納する処理をここに*/
  printf("Numbers: "); 
  printdata(Merge); 
  mergesort(0, N-1);

  return 0;
}

void mergesort(int first, int last){
  if(first < last){
    mergesort(first, (first + last)/2);
    mergesort(((first + last)/2) + 1, last);
    merge_two(first, (first + last)/2, ((first + last)/2) + 1, last);
  }
}

void merge_two(int fr1, int to1, int fr2, int to2){
  int i = 0, sw1 = 0, sw2 = 0, tmp1 = fr1, tmp2 = fr2;  /*sw1, sw2: 真(1)か偽(0)か*/

  for(i = fr1; i <= to2; i++){
    tmpmerge[i] = Merge[i];
  }
  
  i = fr1;
  while(i <= to2){
  //for(i = fr1; i <= to2; i++){
    //printf("***"); printf("tmp1=%d, tmp2=%d, to1=%d, to2=%d\n", tmp1, tmp2, to1, to2);
    //printdata(tmpmerge);
    if((tmpmerge[tmp1] == tmpmerge[tmp2])&&(tmp1 <= to1)&&(tmp2 <= to2)){
      Merge[i] = tmpmerge[tmp1];
      ++tmp1;
      ++i;
      Merge[i] = tmpmerge[tmp2];
      ++tmp2;
      ++i;
      if(tmp1 > to1){
        sw1 = 1;
      }
      if(tmp2 > to2){
        sw2 = 1;
      }
      continue;
    }
    if((tmpmerge[tmp1] < tmpmerge[tmp2])&&(tmp1 <= to1)&&(tmp2 <= to2)){
      Merge[i] = tmpmerge[tmp1];
      ++tmp1;
      ++i;
      if(tmp1 > to1){
        sw1 = 1;
        Merge[i] = tmpmerge[tmp2];
        ++i;
        ++tmp2;
        if(tmp2 > to2){
          break;
        }
        continue;
      }
    }
    if((tmpmerge[tmp1] > tmpmerge[tmp2])&&(tmp1 <= to1)&&(tmp2 <= to2)){
      Merge[i] = tmpmerge[tmp2];
      ++tmp2;
      ++i;
      if(tmp2 > to2){
        sw2 = 1;
        Merge[i] = tmpmerge[tmp1];
        ++tmp1;
        ++i;
        if(tmp1 > to1){
          break;
        }
        continue;
      }
    }
    if((sw1 == 1)&&(sw2 == 0)){
      Merge[i] = tmpmerge[tmp2];
      ++i;
      ++tmp2;
      if(tmp2 > to2){
        sw2 = 1;
      }
    }
    if((sw1 == 1)&&(sw2 == 1)){
      break;
    }
    if((sw2 == 1)&&(sw1 == 0)){
      Merge[i] = tmpmerge[tmp1];
      ++i;
      ++tmp1;
      if(tmp1 > to1){
        sw1 = 1;
      }
    }
    if((sw1 == 1)&&(sw2 == 1)){
      break;
    }
  }
  printf("fr1=%d, to1=%d, fr2=%d, to2=%d\n", fr1, to1, fr2, to2);
  printdata(Merge);
}

void printdata(int data[]){
  int i;

  for(i = 0; i < N; i++){
    printf("%d ", data[i]);
  }
  printf("\n");
}
