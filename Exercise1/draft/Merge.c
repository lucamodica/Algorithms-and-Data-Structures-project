#include <stdlib.h>
#include <stdio.h>

#define max 100

int insert_array(int arr[]) {
  int n, i;
  printf("Quanti elementi sono presenti?: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
  	printf("elemento %d: ", i);
  	scanf("%d", &arr[i]);
  }
  return(n);
}

void stampa_array(int arr[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return;
}

void merge(int arr[], int p, int q, int r) {
  int i, j, k = 0, b[max];
  i = p;
  j = q + 1;

  while (i <= q && j <= r) {
    if (arr[i] < arr[j]) {
      b[k] = arr[i];
      i++;
    } else {
      b[k] = arr[j];
      j++;
    }
    k++;
  }
  while (i <= q) {
    b[k] = arr[i];
    i++;
    k++;
  }
  while (j <= r) {
    b[k] = arr[j];
    j++;
    k++;
  }
  for (k = p; k <= r; k++)
    arr[k] = b[k-p];
  return;
}

void mergee(int a[], int l, int m, int r){
	int n1 = m - l + 1; /* DX array size */
	int n2 = r - m; /* SX array size */
	int L[n1];
	int R[n2];
	int i,j,k;	

	/* fill the auxiliary array */
	for(i=0;i<n1;i++){
	  L[i] = a[l + i];
	}
	for(j=0;j<n2;j++){
	  R[j] = a[m + 1 + j];
	}	

	/* Order part (merge) */
	i = 0;
	j = 0;
	k = l;
	while(i < n1 && j < n2){
	  if(L[i] <= R[j]){
	    a[k] = L[i];
	    i++;
	  }
	  else{
	    a[k] = R[j];
	    j++;
	  }
	  k++;
	}	

	/* Copying the remaining items (if there's any) */
	while(i < n1){
	  a[k] = L[i];
	  i++;
	  k++;
	}
	while(j < n2){
	  a[k] = R[j];
	  j++;
	  k++;
	}	

}

void mergeSort(int a[], int p, int r) {
  int q;
  if (p < r) {
    q = (p + r)/2;
    mergeSort(a, p, q);
    mergeSort(a, q + 1, r);
    merge(a, p, q, r);
  }
}

int main(void) {
  int arr[10] = {10,4,2,6,7,11,9,23,8,9};
  mergeSort(arr, 0, 9);
  stampa_array(arr, 10);
  return 0;
}