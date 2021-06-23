/* Draft file where we binary insertion sort on files with records */ 
#include "record-management.h"


int binary_search(Record **arr, int x, int l, int r){
  /* Check for an array of 2 elements */ 
  if(r <= l){
    return (x > arr[l]->integer_field) ? (l+1) : l;
  }

  /* Compute mean of the range */ 
  int mean = (l+r)/2;

  /* Positive case in which we find the element searched */ 
  if(x == arr[mean]->integer_field){
    return mean;
  }

  /* Check if the element is in the right part of the array */ 
  if (x > arr[mean]->integer_field){
    return binary_search(arr, x, mean + 1, r);
  }
  
  /* Check if the element is in the left part of the array */
  return binary_search(arr, x, l, mean - 1); 
}

void bin_insertion_sort(Record **arr, int length){
  /* Variables */ 
  int i, j, pos;
  Record *elem;

  /* Loop that itarates throughout the array */ 
  for(i = 1; i < length; i++){
    /* Save the element to be moved */ 
    elem = arr[i];

    /* Search for the index where insert element with binary search */ 
    pos = binary_search(arr, elem->integer_field, 0, i);

    /* Move all the element to the right */ 
    for (j = i - 1; j >= pos; j--){
      arr[j+1] = arr[j];
    }
    /* Insert the current element */ 
    arr[j+1] = elem;
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
	printf("Size array: %d\n", size);
	/* Order the array based on the binary insertion sort algorithm */ 
	bin_insertion_sort(recs,size);
	/* Print the ordered array */
  printf("**Print ordered records with binary insertion sort (sorted by integer field)**\n\n");	
	print_array(recs,size);

	exit(EXIT_SUCCESS);
}


