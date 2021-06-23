#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Alternatively, we can use
// #pragma once

/*
 * An array of any number of elements of any kind, ordered in non descending
 * order according to a specific precedence relation
 */
typedef struct _OrderedArray OrderedArray;

/* It creates an empty ordered array and returns the created ordered array.
 * It accepts as input a pointer to a function implementing the precedence
 * relation between the array elements. Such a function must accept as input
 * two pointers to elements and return 0 iff the first element does NOT precede
 * the second one and a number different from zero otherwise.
 * The input parameter cannot be NULL
 */
OrderedArray *ordered_array_create(int (*precdes)(void*, void*));

/* It accepts as input a pointer to an ordered array and
 * it returns 1 iff the ordered array is empty (0 otherwise).
 * The input parameter cannot be NULL
 */
int ordered_array_is_empty(OrderedArray*);

/* It accepts as input a pointer to an ordered array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL
 */
unsigned long ordered_array_size(OrderedArray*);

/* It accepts as input a pointer to an ordered array and a pointer to an
 * element. It adds the element to the ordered array in the right position.
 * The input parameters cannot be NULL
 */
void ordered_array_add(OrderedArray*, void*);

/* It accepts as input a pointer to an ordered array and an integer "i" and
 * it returns the pointer to the i-th element of the ordered array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the ordered array
 */
void *ordered_array_get(OrderedArray*, unsigned long);

/* It accepts as input a pointer to an ordered array and
 * it frees the memory allocated to store the ordered array.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the ordered array was created. The input parameters cannot be NULL
 */
void ordered_array_free_memory(OrderedArray*);


void mbi_sort(OrderedArray *arr, int l, int r);
void merge(OrderedArray *arr, int l, int m, int r);
int binary_search(OrderedArray *arr, void *x, int l, int r);
void bin_insertion_sort(OrderedArray *arr, int l, int r);

#endif // ORDERED_ARRAY_H

