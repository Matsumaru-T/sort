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

// 中央値を求める関数
int median(int A[], int n){
  int i, j;
// 元の配列を壊したくないのでコピーを作る
  int B[n];
  for(i = 0; i < n; i++){
    B[i] = A[i];
  }
// ソートをする
  for(i = 1; i < n; i++){
    j = i;
    while((j>0)&&(B[j-1]>B[j])){
      swap(B+j-1, B+j);
      j--;
    }
  }
// 中央値を返す
  return B[n/2];
}

// pivotを決める関数
int make_pivot(int A[], int n){
  int size;
  int m = (n+4)/5;
  int B[m];
  for(int i = 0; i < m; i++){
    size = n-5*i > 5 ? 5 : n-5*i;
    B[i] = median(A+5*i, size);
  }
  return median(B, m);
}

int quick_select(int A[], int n, int k){
  int i, j, pivot;

  pivot = A[n/2];
  A[n/2] = A[0];
  A[0] = pivot;
  for(i = j = 1; i < n; i++){
    if(A[i] <= pivot){
      swap(A+i, A+j);
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A+1, j-1, k);
}

int median_of_median(int A[], int n, int k){
  if(n <= 5){
    return quick_select(A, n, n/2);
  }else{
    // 5個ずつに分けた配列の中央値を格納する配列Bを作る
    int size, m = (n+4)/5, B[m], pivot, i, j;
    for(i = 0; i < m; i++){
      size = n-5*i > 5 ? 5 : n-5*i;
      B[i] = median(A+5*i, size);
    }

    // pivotを再帰で決定
    pivot = median_of_median(B, m, m/2);

    // A[j]==pivotとなるjを決める
    for(i = 0; i < n; i++){
      if(A[i] == pivot) j = i;
    }

    // A[j]とA[0]を入れ替え
    A[j] = A[0];
    A[0] = pivot;

    for(i = j = 1; i < n; i++){
      if(A[i] <= pivot){
        swap(A+i, A+j);
        j++;
      }
    }

    if(j == k+1) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+1, j-1, k);
  }
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(median_of_median(A, N, i) != i) printf("ERROR %d %d\n", i, median_of_median(A, N, i));
    printf("%d th element is %d\n", i, median_of_median(A, N, i));
  }
}
