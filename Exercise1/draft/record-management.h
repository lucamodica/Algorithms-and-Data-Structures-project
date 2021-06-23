/* Header funzction/data structures for file management with record */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 100
#define BUFFER_SIZE 1024

typedef struct _record {
	char *string_field;
	int integer_field;
} Record;

int load_array(char *file_name, Record **arr);

void print_array_int_first(Record **arr, int l, int r);

void print_array_str_first(Record **arr, int l, int r);