#include <string.h>
#include "ordered_array.h"

#define BUFFER_SIZE 1024

typedef struct _record {
  char *string_field;
  int integer_field;
} Record;

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the integer field of the first record is smaller than
 * the integer field of the second one (0 otherwise)
*/
static int precedes_record_int_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field < rec2_p->integer_field;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is smaller than
 * the string field of the second one (0 otherwise)
 */
static int precedes_record_string_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

static  void free_array(OrderedArray *array) {
  unsigned long size = ordered_array_size(array);
  for (unsigned long i = 0; i < size; ++i) {
    Record *array_element = (Record*)ordered_array_get(array, i);
    free(array_element->string_field);
    free(array_element);
  }
  ordered_array_free_memory(array);
}

static  void print_array(OrderedArray *array) {
  unsigned long size = ordered_array_size(array);

  Record *array_element;
  printf("\nORDERED ARRAY OF RECORDS\n");

  for (unsigned long i = 0; i < size; ++i) {
    array_element = (Record*)ordered_array_get(array, i);
    printf("%s, %d\n", array_element->string_field, array_element->integer_field);
  }
}

static void load_array(const char *file_name, OrderedArray *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    Record *record_p = malloc(sizeof(Record));
    if (record_p == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }

    char *string_field_in_read_line_p = strtok(buffer, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");

    record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));
    if (record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atoi(integer_field_in_read_line_p);
    ordered_array_add(array, (void*)record_p);
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static void test_with_comparison_function(const char *file_name, int (*compare)(void*, void*)) {
  OrderedArray *array = ordered_array_create(compare);
  load_array(file_name, array);
  print_array(array);
  free_array(array);
}

//It should be invoked with one parameter specifying the filepath of the data file
int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: ordered_array_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
  test_with_comparison_function(argv[1], precedes_record_int_field);
  test_with_comparison_function(argv[1], precedes_record_string_field);

  return EXIT_SUCCESS;
}
