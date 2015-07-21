#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8
int Merge[N], tmpmerge[N];

void printdata(int data[]);  /*ソートの途中経過や結果の出力*/
void m_sort(int first, int last);  /*関数名mergesortはstdlib.hのmergesortと
                                    *競合してしまうためm_sortにした
                                    */
void merge_two(int fr1, int to1, int fr2, int to2);


int main(void){
  int i;

  /*1~100の乱数を発生させ、Merge[]に格納*/
  srand((unsigned int)time(0));
  for(i = 0; i < N; i++){
    Merge[i] = rand() % 100 + 1;
  }
 
  printf("Numbers: "); 
  printdata(Merge); 
  m_sort(0, N-1);

  return 0;
}

void m_sort(int first, int last){
  if(first < last){
    m_sort(first, (first + last)/2);
    m_sort(((first + last)/2) + 1, last);
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
    if((sw1 == 0)&&(sw2 == 0)){
      if(tmpmerge[tmp1] == tmpmerge[tmp2]){
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
      }else if(tmpmerge[tmp1] < tmpmerge[tmp2]){
        Merge[i] = tmpmerge[tmp1];
        ++tmp1;
        ++i;
        if(tmp1 > to1){
          sw1 = 1;
        }
      }else if(tmpmerge[tmp1] > tmpmerge[tmp2]){
        Merge[i] = tmpmerge[tmp2];
        ++tmp2;
        ++i;
        if(tmp2 > to2){
          sw2 = 1;
        }
      }
    }else if((sw1 == 1)&&(sw2 == 0)){
      Merge[i] = tmpmerge[tmp2];
      ++tmp2;
      ++i;
      if(tmp2 > to2){
        sw2 = 1;
      }
    }else if((sw2 == 1)&&(sw1 == 0)){
      Merge[i] = tmpmerge[tmp1];
      ++tmp1;
      ++i;
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
