/* Draft file where we try merge sort on files */ 
#include <time.h>
#include "record-management.h"


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

void merge_sort(Record **arr, int l, int r){
	if (l < r){
		int m = (l+r)/2;
		merge_sort(arr,l,m);
		merge_sort(arr,m + 1,r);
		merge(arr,l,m,r);
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
	printf("Size array: %d\n\n", size);

  /* Start measure merge sort time */ 
  struct timespec begin, end; 
  clock_gettime(CLOCK_REALTIME, &begin);
  
	/* Order the array based on the merge sort algorithm */ 
	merge_sort(recs,0,size-1);

  /* calculate the time passed */
  clock_gettime(CLOCK_REALTIME, &end);
  long seconds = end.tv_sec - begin.tv_sec;
  long nanoseconds = end.tv_nsec - begin.tv_nsec;
  double elapsed = seconds + nanoseconds*1e-9;
  printf("Time measured: %.5f seconds.\n", elapsed);

	/* Print the ordered array */
  printf("**Print ordered records with merge sort (sorted by string field)**\n\n");	
	print_array(recs,0,size-1);

	exit(EXIT_SUCCESS);
}

