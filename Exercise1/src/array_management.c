/* Implementation of the function in the header file */ 
#include "array_management.h"


/* ***INTERNAL SORTING FUNCTION*** */ 
/**
 * @brief Part of the hybrid array-sorting function (order_array()) for large portions.
 * 
 * @param ordered_array The array to be ordered.
 * @param l The leftmost range limit.
 * @param r The rightmost range limit.
 */
static void merge(OrderedArray *, int, int, int);

/**
 * @brief Used with bin_insertion_sort func, it searches for the index where to insert 
 * the element.
 * 
 * @param ordered_array The array to be ordered.
 * @param element The element to be inserted.
 * @param l The leftmost range limit.
 * @param r The rightmost range limit.
 * @return The index where the element will be inserted. 
 */
static int binary_search(OrderedArray *, void *, int, int);

/**
 * @brief Part of the hybrid sorting array for little portions (in our
 * case, it will be also used standalone for benchmarking purpose)
 * 
 * @param ordered_array The array to be ordered.
 */
static void bin_insertion_sort(OrderedArray *,  int, int);



OrderedArray *array_create(int (*precedes)(void*, void*)) {
  if(precedes == NULL) {
    fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  /* Initialize OrderedArray element */ 
  OrderedArray *ordered_array = (OrderedArray*) malloc(sizeof(OrderedArray));
  if(ordered_array == NULL) {
    fprintf(stderr, "ordered_array_create: unable tu alloc memory for ordered array");
    exit(EXIT_FAILURE);
  }

  /* Initialize the array attribute */ 
  ordered_array->array = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));
  if(ordered_array->array == NULL) {
    fprintf(stderr, "oredered_array_create: uneble to create memory for the internal array");
    exit(EXIT_FAILURE);
  }

  ordered_array->size = 0;
  ordered_array->array_capacity = INITIAL_CAPACITY;
  ordered_array->precedes = precedes;
  return ordered_array;
}

int is_array_empty(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return ordered_array->size == 0;
}

int array_size(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return ordered_array->size;
}

void array_add(OrderedArray *ordered_array, void *element) {
  if (ordered_array == NULL) {
    fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  /* Check if the actual array size excedes its capacity */ 
  if (ordered_array->size >= ordered_array->array_capacity) {
    ordered_array->array_capacity = 2 * ordered_array->array_capacity;
    ordered_array->array = (void**)realloc(ordered_array->array, (size_t) ordered_array->array_capacity * sizeof(void*));
    if (ordered_array->array == NULL) {
      fprintf(stderr,"array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }

  /* insert the element */ 
  ordered_array->array[ordered_array->size] = element;
  ordered_array->size++;
}

void *array_get(OrderedArray *ordered_array, int i) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->size) {
    fprintf(stderr, "ordered_array_get: Index %d is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return ordered_array->array[i];
}

void array_free_memory(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "array_free_memory: array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->array);
  free(ordered_array);
}


void order_array(OrderedArray *ordered_array, int l, int r){
  if (l < r){
		int m = (l+r)/2;
    int len_inn_array = (r-l)+1;
    
    if(len_inn_array > 300){
		  order_array(ordered_array,l,m);
		  order_array(ordered_array,m + 1,r);
      merge(ordered_array,l,m,r);
    }
    else{
      bin_insertion_sort(ordered_array,l,r);
    }
	}
}

static void merge(OrderedArray *ordered_array, int l, int m, int r){
  /* Init values */ 
	int nL = m - l + 1; /* SX array size */
  int nR = r - m; /* DX array size */
  int i, j, k;

	/* Allocating auxiliary array */
	void **L = (void**) calloc((size_t) nL,sizeof(void*));
	void **R = (void**) calloc((size_t) nR,sizeof(void*));

  /* fill the auxiliary array */
  for(i=0; i < nL; i++){
    L[i] = malloc(sizeof(void *));
    L[i] = ordered_array->array[l + i];
  }
  for(j=0; j < nR;  j++){
    R[j] = malloc(sizeof(void *));
    R[j] = ordered_array->array[m + 1 + j];
  }
  
  /* Order part (merge) */
  i = 0;
  j = 0;
  k = l;
  while(i < nL && j < nR){
    if(ordered_array->precedes(L[i], R[j]) <= 0){
      ordered_array->array[k] = L[i];
      i++;
    }
    else{
      ordered_array->array[k] = R[j];
      j++;
    }
    k++;
  }

  /* Copying the remaining items (if there's any) */
  while(i < nL){
    ordered_array->array[k] = L[i];
    i++;
    k++;
  }
  while(j < nR){
    ordered_array->array[k] = R[j];
    j++;
    k++;
  }	

  /* Free auxiliary array */
	free(L);
	free(R);
}

int binary_search(OrderedArray *ordered_array, void *x, int l, int r){
  /* Check for an array of 2 elements */ 
  if(r <= l){
    return (ordered_array->precedes(x,ordered_array->array[l]) > 0) ? (l + 1) : l;
  }

  /* Compute mean of the range */ 
  int mean = (l + r) / 2;

  /* Positive case in which we find the element searched */ 
  if(x == ordered_array->array[mean]){
    return mean;
  }

  /* Check if the element is in the right part of the array */ 
  if (ordered_array->precedes(x,ordered_array->array[mean]) > 0){
    return binary_search(ordered_array, x, mean + 1, r);
  }
  
  /* Check if the element is in the left part of the array */
  return binary_search(ordered_array, x, l, mean - 1); 
}

static void bin_insertion_sort(OrderedArray *ordered_array, int l, int r){
  /* Variables */ 
  int i, j, pos;
  void *elem;

  /* Loop that itarates throughout the array */ 
  for(i = l; i <= r; i++){
    /* Save the element to be moved */ 
    elem = ordered_array->array[i];

    /* Search for the index where insert element with binary search */ 
    pos = binary_search(ordered_array, elem, l, i);

    /* Move all the element to the right */ 
    for (j = i - 1; j >= pos; j--){
      ordered_array->array[j+1] = ordered_array->array[j];
    }
    /* Insert the current element */ 
    ordered_array->array[j+1] = elem;
  }
  
}

