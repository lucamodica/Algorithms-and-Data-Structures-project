#include "ordered_array.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

//static unsigned long get_index_to_insert(OrderedArray *ordered_array, void *element);
//static void insert_element(OrderedArray *ordered_array, void *element, unsigned long index);

//It represents the internal structure of this implementation of ordered arrays
struct _OrderedArray {
  void **array;
  unsigned long size;
  unsigned long array_capacity;
  int (*precedes)(void*, void*);
};

OrderedArray *ordered_array_create(int (*precedes)(void*, void*)) {
  if (precedes == NULL) {
    fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  OrderedArray *ordered_array = (OrderedArray*)malloc(sizeof(OrderedArray));
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ordered_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if (ordered_array->array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  ordered_array->size = 0;
  ordered_array->array_capacity = INITIAL_CAPACITY;
  ordered_array->precedes = precedes;
  return ordered_array;
}

int ordered_array_is_empty(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return ordered_array->size == 0;
}

unsigned long ordered_array_size(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return ordered_array->size;
}

void ordered_array_add(OrderedArray *ordered_array, void *element) {
  if (ordered_array == NULL) {
    fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (ordered_array->size >= ordered_array->array_capacity) {
    ordered_array->array_capacity = 2 * ordered_array->array_capacity; // Why multiply by 2?
    ordered_array->array = (void**)realloc(ordered_array->array, ordered_array->array_capacity * sizeof(void*));
    if (ordered_array->array == NULL) {
      fprintf(stderr,"ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  //unsigned long index = get_index_to_insert(ordered_array, element);
  //insert_element(ordered_array, element, index);
  ordered_array->array[ordered_array->size] = element;
  ordered_array->size++;
  mbi_sort(ordered_array,0,ordered_array->size-1);
}

void *ordered_array_get(OrderedArray *ordered_array, unsigned long i) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->size) {
    fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return ordered_array->array[i];
}

void ordered_array_free_memory(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->array);
  free(ordered_array);
}


//returns the position where the new element must be inserted
/*
static unsigned long get_index_to_insert(OrderedArray *ordered_array, void *element) {
  unsigned long i = 0;

  while (i < ordered_array->size) {
    // this would be an equivalent call
    // if ((*ordered_array->precedes)(element, ordered_array->array[i])) {
    if (ordered_array->precedes(element, ordered_array->array[i]))
      break;
    i++;
  }
  return i;
}
*/

//inserts the specified element in the specified ordered array at the specified index position
/*
static void insert_element(OrderedArray *ordered_array, void *element, unsigned long index) {
  for (unsigned long i = ordered_array->size; i > index; --i)
    ordered_array->array[i] = ordered_array->array[i-1];
  ordered_array->array[index] = element;
}
*/

void mbi_sort(OrderedArray *arr, int l, int r){

  if (l < r){
		int m = (l+r)/2;
    int len_inn_array = (r-l)+1;
    
    if(len_inn_array > sqrt(arr->size)){
		  mbi_sort(arr,l,m);
		  mbi_sort(arr,m + 1,r);
      merge(arr,l,m,r);
    }
    else{
      bin_insertion_sort(arr,l,r);
    }
	}
}

void merge(OrderedArray *arr, int l, int m, int r){
	/* Init values */ 
	int nL = m - l + 1; /* SX array size */
  int nR = r - m; /* DX array size */
  int i, j, k;

	/* Allocating auxiliary array */
	void **L = (void**) calloc(nL,sizeof(void*));
	void **R = (void**) calloc(nR,sizeof(void*));

  /* fill the auxiliary array */
  for(i=0; i < nL; i++){
    L[i] = malloc(sizeof(void *));
    L[i] = arr->array[l + i];
  }
  for(j=0; j < nR;  j++){
    R[j] = malloc(sizeof(void *));
    R[j] = arr->array[m + 1 + j];
  }
  
  /* Order part (merge) */
  i = 0;
  j = 0;
  k = l;
  while(i < nL && j < nR){
    if(arr->precedes(L[i], R[j]) <= 0){
      arr->array[k] = L[i];
      i++;
    }
    else{
      arr->array[k] = R[j];
      j++;
    }
    k++;
  }

  /* Copying the remaining items (if there's any) */
  while(i < nL){
    arr->array[k] = L[i];
    i++;
    k++;
  }
  while(j < nR){
    arr->array[k] = R[j];
    j++;
    k++;
  }	

  /* Free auxiliary array */
  /*
  for(i=0; i < nL; i++){
    free(L[i]);
  }
  for(j=0; j < nR; j++){
    free(R[j]);
  }*/
	free(L);
	free(R);
}

int binary_search(OrderedArray *arr, void *x, int l, int r){
  /* Check for an array of 2 elements */ 
  if(r <= l){
    return (arr->precedes(x,arr->array[l]) > 0) ? (l+1) : l;
  }
  
  
  /* Compute mean of the range */ 
  int mean = (l+r)/2;

  /* Positive case in which we find the element searched */ 
  if(arr->precedes(x,arr->array[l]) == 0){
    return mean;
  }

  /* Check if the element is in the right part of the array */ 
  if (arr->precedes(x,arr->array[mean]) > 0){
    return binary_search(arr, x, mean + 1, r);
  }
  
  /* Check if the element is in the left part of the array */
  return binary_search(arr, x, l, mean - 1); 
}

void bin_insertion_sort(OrderedArray *arr, int l, int r){
  /* Variables */ 
  int i, j, pos;
  void *elem;

  /* Loop that itarates throughout the array */ 
  for(i = l; i <= r; i++){
    /* Save the element to be moved */ 
    elem = arr->array[i];

    /* Search for the index where insert element with binary search */ 
    pos = binary_search(arr, elem, l, i);

    /* Move all the element to the right */ 
    for (j = i - 1; j >= pos; j--){
      arr->array[j+1] = arr->array[j];
    }
    /* Insert the current element */ 
    arr->array[j+1] = elem;
  }
  
}



