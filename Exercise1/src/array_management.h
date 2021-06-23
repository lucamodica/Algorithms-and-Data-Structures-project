#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Initial array capcity */ 
#define INITIAL_CAPACITY 2

/* Struct that represents the internal structure of this 
implementation of ordered arrays */ 
struct _OrderedArray {
  void **array; /* Point to the array content */ 
  int size; /* Current generic array size */ 
  int array_capacity; /* Current array capacity */ 
  int (*precedes)(void*, void*); /* Takes 2 void** parameters, return the */
};
typedef struct _OrderedArray OrderedArray;


/**
 * @brief Creates a generic array.
 * 
 * @param precedes The function pointer used to specify
 * how the elements precedes each other.
 * 
 * @return The array created.
 */
OrderedArray *array_create(int (*precedes)(void*, void*));

/**
 * @brief Checks if the array is empty. In particular the check
 * will be done on the size attribute.
 * 
 * @return 1 if the array is empty, 0 otherwise.
 */
int is_array_empty(OrderedArray*);

/**
 * @brief Returns the array size.
 * 
 * @return The size attribute.
 */
int array_size(OrderedArray*);

/**
 * @brief Adds an element to the array, maintaining
 * the array order.
 */
void array_add(OrderedArray*, void*);

/**
 * @brief Gets the element at a specific index.
 * 
 * @param long Index of the element desired.
 * @return The element at the specific index.
 */
void *array_get(OrderedArray*, int);

/**
 * @brief Frees the memory occupied by the 
 * Ordered Array structure created before.
 */
void array_free_memory(OrderedArray *);

/**
 * @brief Sorts the array based on the "precedes" function criteria, 
 * using an hybrid sorting algorithm between merge sort and 
 * binary-insertion sort to order the array.
 * The algorithm will use merge sorting part or binary 
 * insertion sorting based on the array portion length.
 * 
 * @param ordered_array The array to be ordered.
 * @param l The leftmost range limit.
 * @param r The rightmost range limit.
 */
void order_array(OrderedArray *, int, int);

#endif  //ORDERED_ARRAY_H