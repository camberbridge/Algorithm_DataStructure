#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Nmax 10000000

int Bubble[Nmax], Quick[Nmax], Merge[Nmax], tmpmerge[Nmax], N;

void bubblesort();
void swap(int sw1, int sw2);
void quicksort(int from, int to);
void m_sort(int first, int last);  /*関数名mergesortはstdlib.hのmergesortと
                                    *競合してしまうためm_sortにした
                                    */
void merge_two(int fr1, int to1, int fr2, int to2);

int main(void){
  int i;
  double t, x, y, z;  /*t: ソート処理前のclock, x: バブルソート実行時間, 
                       *y: クイックソート実行時間, z: マージソート実行時間
                       */

  printf("N? ");
  scanf("%d", &N);

  /*set random numbers Bubble[], Quick[], Merge[]*/
  srand((unsigned int)time(0));
 
  for(i = 0; i < N; i++){
    Bubble[i] = Quick[i] = Merge[i] = (rand() % 10000) + 1;
  }

  t = clock();
  bubblesort();
  x = (clock() - t) / CLOCKS_PER_SEC;
  printf("Bubble Sort %g sec \n", x);

  t = clock();
  quicksort(0, N - 1);
  y = (clock() - t) / CLOCKS_PER_SEC;
  printf("Quick Sort %g sec \n", y);

  t = clock();
  m_sort(0, N - 1);
  z = (clock() - t) / CLOCKS_PER_SEC;
  printf("Merge Sort %g sec \n", z);

  return 0;
}

/***ここからバブルソート***/
void bubblesort(){
  int i, j, tmp;

  for(i = 0; i < N-1; i++){
    for(j = N-1; j > i; j--){
      if(Bubble[j-1] > Bubble[j]){
        tmp = Bubble[j];
        Bubble[j] = Bubble[j-1];
        Bubble[j-1] = tmp;
      }
    }
  }
}
/***ここまでバブルソート***/

/***ここからクイックソート***/
void swap(int sw1, int sw2){
  int tmp;
  tmp = Quick[sw1];
  Quick[sw1] = Quick[sw2];
  Quick[sw2] = tmp;
}

void quicksort(int from, int to){
  if(from < to){
    int pivot = Quick[from];
    int less = from, greater = from + 1, i;
    
    for(i = greater; i <= to; i++){
      if(Quick[i] < pivot){
        less++;
        swap(less, i);
      }
    }
    Quick[from] = Quick[less];
    Quick[less] = pivot;
    
    quicksort(from, less - 1);
    quicksort(less + 1, to);
  }
}
/***ここまでクイックソート***/

/***ここからマージソート***/
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
}
/***ここまでマージソート***/
