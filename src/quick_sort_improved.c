#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}


/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
  int i, j, l, pivot;

// 真ん中の要素をピボットとする
  pivot = A[n/2];
  A[n/2] = A[0];
  A[0] = pivot;

// A[0], ... , A[j-1] が pivot と等しくなるようにする
  for(i = j = 1; i < n; i++){
    if(A[i] == pivot){
      swap(A+i, A+j);
      j++;
    }
  }

  l = j;

// A[j], ... , A[l-1] が pivot 未満
  for(i = j; i < n; i++){
    if(A[i] < pivot){
      swap(A+i, A+l);
      l++;
    }
  }

//{pivot未満}{pivotと等しい}{pivotより大きい}の順に並び替える
  for(i = 0; i < l-j; i++){
    swap(A+i,A+j+i);
  }

  if(n > 0){
    quick_sort(A,l-j);
    quick_sort(A+l,n-l);
  }
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
