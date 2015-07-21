#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Nmax 100
int Bubble[Nmax], Quick[Nmax], N;

void printdata(int data[]);  /*ソートの途中経過や結果の出力*/
void bubblesort();
void swap(int sw1, int sw2);  /*sw1とsw2の入れ替え*/
void quicksort(int from, int to);  /*Quick[from]をピボットとして、
                                    *Quick[from]からQuick[to]まで
                                    *をクイックソート*/

int main(void){
  int i;

  printf("N?");
  scanf("%d", &N);
  /*1~10000の乱数を発生させ、Bubble[], Quick[]に格納*/
  srand((unsigned int)time(0));
  for(i = 0; i < N; i++){
    Bubble[i] = Quick[i] = rand() % 10000 + 1;
  }
  printf("Input: ");
  for(i = 0; i < N; i++){
    printf("%d ", Bubble[i]);
    if(i % 10 == 9){
      printf("\n");
    }
  }
  printf("\n");

  /*****BubbleSort*****/
  printf("Bubble Sort start\n");
  bubblesort();  /*Bubble[0]~Bubble[N-1]をソート*/
  printf("Bubble Sort end: ");
  printdata(Bubble);  /*バブルソートの結果出力*/

  /*****QuickSort*****/
  printf("Quick Sort start\n");
  quicksort(0, N-1);  /*Quick[0]~Quick[N-1]をソート*/
  printf("Quick Sort end: ");
  printdata(Quick);  /*クイックソートの結果出力*/
  
  return 0;
}

void bubblesort(){
  int i, j, tmp;

  for(i = 0; i < N-1; i++){  /*配列の要素分だけ回す*/
    for(j = N-1; j > i; j--){  /*配列の末尾から先頭へじゅんぐり*/
      if(Bubble[j-1] > Bubble[j]){  /*前に位置する要素の方が大き
                                     *かったら入れ替える*/
        tmp = Bubble[j];
        Bubble[j] = Bubble[j-1];
        Bubble[j-1] = tmp;
        printdata(Bubble);
      }
    }
    printdata(Bubble);
  }
}

void printdata(int data[]){
  int i;
  
  for(i = 0; i < N; i++){
    printf("%d ", data[i]);
  }
  printf("\n");
}

void swap(int sw1, int sw2){
  int tmp;
  tmp = Quick[sw1];
  Quick[sw1] = Quick[sw2];
  Quick[sw2] = tmp;
}

void quicksort(int from, int to){
  if(from < to){
    /*****ここからPartition*****/
    int pivot = Quick[from];  /*配列の先頭をピボットにする*/
    int less = from, greater = from + 1, i;
    printf("from=%d, to=%d, pivot=%d\n", from + 1, to + 1, pivot);    
 
    for(i = greater; i <= to; i++){
      if(Quick[i] < pivot){  /*ピボットより小さい要素が出現したら
                              *lessをインクリメントしてそれと入れ
                              *替える*/
        less++;
        swap(less, i);
      }
    }
    Quick[from] = Quick[less];
    Quick[less] = pivot;
    printdata(Quick);
    /*****ここまでPartition*****/

    quicksort(from, less - 1);  /*小グループのクイックソート再起*/
    quicksort(less + 1, to);  /*大グループのクイックソート再起*/
  }
}
