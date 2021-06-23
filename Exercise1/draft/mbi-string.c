/* Draft file where we try merge sort on files */ 
#include <time.h>
#include <math.h>
#include "record-management.h"

int binary_search(Record **arr, char* x, int l, int r){
  /* Check for an array of 2 elements */ 
  if(r <= l){
    return (strcmp(x, arr[l]->string_field) > 0) ? (l+1) : l;
  }

  /* Compute mean of the range */ 
  int mean = (l+r)/2;

  /* Positive case in which we find the element searched */ 
  if(strcmp(x, arr[mean]->string_field) == 0){
    return mean;
  }

  /* Check if the element is in the right part of the array */ 
  if (strcmp(x, arr[mean]->string_field) > 0){
    return binary_search(arr, x, mean + 1, r);
  }
  
  /* Check if the element is in the left part of the array */
  return binary_search(arr, x, l, mean - 1); 
}

void bin_insertion_sort(Record **arr, int l, int r){
  /* Variables */ 
  int i, j, pos;
  Record *elem;

  /* Loop that itarates throughout the array */ 
  for(i = l; i <= r; i++){
    /* Save the element to be moved */ 
    elem = arr[i];

    /* Search for the index where insert element with binary search */ 
    pos = binary_search(arr, elem->string_field, l, i);

    /* Move all the element to the right */ 
    for (j = i - 1; j >= pos; j--){
      arr[j+1] = arr[j];
    }
    /* Insert the current element */ 
    arr[j+1] = elem;
  }

  //print_array_str_first(arr,l,r);
  //printf("\n\n");
  
}

void merge(Record **arr, int l, int m, int r){
	/* Init values */ 
	int nL = m - l + 1; /* SX array size */
  int nR = r - m; /* DX array size */
  int i, j, k;

	/* Allocating auxiliary array */
	Record **L = (Record**) calloc(nL,sizeof(Record*));
	Record **R = (Record**) calloc(nR,sizeof(Record*));

  /* fill the auxiliary array */
  for(i=0; i < nL; i++){
    L[i] = malloc(sizeof(Record *));
    *L[i] = *arr[l + i];
  }
  for(j=0; j < nR;  j++){
    R[j] = malloc(sizeof(Record *));
    *R[j] = *arr[m + 1 + j];
  }
  
  /* Order part (merge) */
  i = 0;
  j = 0;
  k = l;
  while(i < nL && j < nR){
    if(strcmp(L[i]->string_field, R[j]->string_field) <= 0){
      *arr[k] = *L[i];
      i++;
    }
    else{
      *arr[k] = *R[j];
      j++;
    }
    k++;
  }

  /* Copying the remaining items (if there's any) */
  while(i < nL){
    *arr[k] = *L[i];
    i++;
    k++;
  }
  while(j < nR){
    *arr[k] = *R[j];
    j++;
    k++;
  }	

  /* Free auxiliary array */
  for(i=0; i < nL; i++){
    free(L[i]);
  }
  for(j=0; j < nR; j++){
    free(R[j]);
  }
	free(L);
	free(R);
}

void mbi_sort(Record **arr, int size, int l, int r){

  if (l < r){
		int m = (l+r)/2;
    int len_inn_array = (r-l)+1;
    
    if(len_inn_array > sqrt(size)){
		  mbi_sort(arr,size,l,m);
		  mbi_sort(arr,size,m + 1,r);
      merge(arr,l,m,r);
    }
    else{
      bin_insertion_sort(arr,l,r);
    }
	}
}


/* **MAIN** */ 
int main(int argc, char *argv[]) {
	if(argc < 2){
	  printf("Usage: merge-sort <file_name>\n");
	  exit(EXIT_FAILURE);
	}
	int size = 0;

	/* Allocating the array */ 
	Record **recs = (Record**) malloc(sizeof(Record *)*SIZE);
	/* Loading the array */
	size = load_array(argv[1],recs);
	printf("Size array: %d, sqrt(size): %d \n\n", size, (int) sqrt(size));

  print_array_str_first(recs,0,size-1);

  /* Start measure merge sort time */ 
  struct timespec begin, end; 
  clock_gettime(CLOCK_REALTIME, &begin);
  
	/* Order the array based on the merge sort algorithm */ 
	mbi_sort(recs,size,0,size-1);

  /* calculate the time passed */
  clock_gettime(CLOCK_REALTIME, &end);
  long seconds = end.tv_sec - begin.tv_sec;
  long nanoseconds = end.tv_nsec - begin.tv_nsec;
  double elapsed = seconds + nanoseconds*1e-9;
  printf(F_RED "Time measured for sorting: %.5f seconds.\n\n " ENDSTYLE, elapsed); 

	/* Print the ordered array */
  printf("**Print ordered records with merge sort (sorted by STRING FIELD)**\n\n");	
  print_array_str_first(recs,0,size-1);

	exit(EXIT_SUCCESS);
}