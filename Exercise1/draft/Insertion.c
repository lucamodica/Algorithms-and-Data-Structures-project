#include <stdio.h> 

  
int ricercaBin(int arr[], int x, int low, int high){
  if (high <= low)
    return (x > arr[low])?  (low + 1): low;
  
    int mid = (low + high)/2;
  
  if(x == arr[mid])
    return mid + 1;
  
  if(x > arr[mid])
    return ricercaBin(arr, x, mid + 1, high);

  return ricercaBin(arr, x, low, mid - 1);
}
  
// Funzione ch ordina un array[] di lunghezza \'n\'
void insertionSort(int arr[], int n){
  int i, pos, j, elem;
  
  for(i = 1; i < n; ++i){
    j = i - 1;
    elem = arr[i];
  
    // troviamo la posizione in cui "elem" va inserito
    pos = ricercaBin(arr, elem, 0, j);
  
    // Spostiamo tutti gli elementi a destra per far spazio
    while(j >= pos){
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = elem;
  }
}
  
// main per testare la funzione InsertionSort()
int main(){
  int arr[] = {37, 23, 0, 17, 12, 72, 31, 46, 100, 88, 54};
  int n = sizeof(arr)/sizeof(arr[0]), i;
  
  printf("Array iniziale disordinato: \n");
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
  insertionSort(arr, n);
	i = 0;
    printf("\n\nArray ordinato: \n");
    for(i = 0; i < n; i++)
      printf("%d ", arr[i]);
  
  return 0;
}