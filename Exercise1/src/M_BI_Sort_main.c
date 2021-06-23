/* Test with a file to be read */ 
#include "array_management.h"
#include <time.h>

/* Buffer size for reading a data file */ 
#define BUFFER_SIZE 1024

/* Styiling text */
#define F_YELLOW "\x1b[33m" 
#define F_RED "\x1b[31m"
#define F_GREEN "\x1b[32m"
#define ENDSTYLE "\x1b[0m"

typedef struct _record {
  int index;
  char *string_field;
  int integer_field;
  double double_field;
} Record;


/**
 * @brief Start a timer to measure time
 * 
 * @return The struct timespec that keeps track
 * of when the timer started
 */
static struct timespec start_timer(){
  struct timespec begin;
  clock_gettime(CLOCK_REALTIME, &begin);

  return begin;
}

/**
 * @brief Stop a timer and measure time and measure
 * the time passed
 * 
 * @param begin the struct that keeped track of when
 * the timer started
 * @return The time passed, in seconds. 
 */
static double stop_timer(struct timespec begin){
  struct timespec end;
  clock_gettime(CLOCK_REALTIME, &end);

  long seconds = end.tv_sec - begin.tv_sec;
  long nanoseconds = end.tv_nsec - begin.tv_nsec;
  double elapsed = (double) seconds + (double) nanoseconds*1e-9;

  return elapsed;
}


/**
 * @brief Checks which int pointer is smaller (or bigger, 
 * depending on the function).
 * 
 * @param r1_p First pointer to Record
 * @param r2_p Second pointer to Record
 * @return 1 if the integer field of the first record is smaller than
 * the integer field of the second one, 0 otherwise.
 */
static int precedes_record_int_field_cr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_cr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_cr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field > rec2_p->integer_field;
}
static int precedes_record_int_field_decr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_decr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_decr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field < rec2_p->integer_field;
}

/**
 * @brief Checks whitch string pointer is smaller (or bigger, 
 * depending on the function).
 * 
 * @param r1_p First pointer to Record
 * @param r2_p Second pointer to Record
 * @return 1 if the string field of the first record is smaller than
 * the string field of the second one, 0 otherwise. 
 */
static int precedes_record_string_field_cr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_string_cr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_string_cr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) > 0;
}
static int precedes_record_string_field_decr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_string_field_decr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_string_field_decr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

/**
 * @brief Checks whitch double pointer is smaller (or bigger, 
 * depending on the function).
 * 
 * @param r1_p First pointer to Record
 * @param r2_p Second pointer to Record
 * @return It returns 1 if the integer field of the first record is smaller (or
 * bigger, depending on the function) than the double field of the second 
 * one (0 otherwise) 
 */
static int precedes_record_double_field_cr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_cr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_cr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(rec1_p->double_field > rec2_p->double_field){
    return 1;
  } 
  else if(rec1_p->double_field == rec2_p->double_field){
    return 0;
  } 
  else {
    return -1;
  }
}
static int precedes_record_double_field_decr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_decr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_decr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(rec1_p->double_field < rec2_p->double_field){
    return 1;
  } 
  else if(rec1_p->double_field == rec2_p->double_field){
    return 0;
  } 
  else {
    return -1;
  }
}


/* Frees the allocated memory */ 
static void free_array(OrderedArray *array) {
  int size = array_size(array);
  for (int i = 0; i < size; ++i) {
    Record *array_element = (Record*)array_get(array, i);
    free(array_element->string_field);
    free(array_element);
  }
  array_free_memory(array);
}

/**
 * @brief Function that prints the array (on file)
 * 
 * @param array Array to print
 * @param file_name Files used for printing
 */
static void write_array(OrderedArray *array, const char* file_name) {
  int size = array_size(array);
  FILE *fp = fopen(file_name, "w");
  Record *array_element;

  printf("\nWriting sorted data to the file...\n");
  for (int i = 0; i < size; ++i) {
    array_element = (Record*)array_get(array, i);
    fprintf(fp,"%d, %s, %d, %.6f\n", array_element->index, array_element->string_field, 
      array_element->integer_field, array_element->double_field);
  }
  fclose(fp);
  printf("Data write completed!\n");
}

/**
 * @brief Function that loads file, and allocates the memory needed.
 * 
 * @param file_name File to be loaded
 * @param array The array needed
 */
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

    /* Reading the fields of the record */ 
    char *index_read = strtok(buffer, " ,");
    char *string_field_read = strtok(NULL, " ,");
    char *integer_field_read = strtok(NULL, " ,");
    char *double_field_read = strtok(NULL, " ,");

    /* Record memorization */
    record_p->index = atoi(index_read);
    record_p->string_field = malloc((strlen(string_field_read)+1) * sizeof(char));
    if (record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field, string_field_read);
    record_p->integer_field = atoi(integer_field_read);
    record_p->double_field = atof(double_field_read);
    array_add(array, (void*)record_p);
  }
  fclose(fp);
  printf("Data loaded!\n");
}

/**
 * @brief Wrapper function that starts the array loading process, prints the loaded array 
 * and frees the allocated memory once the process terminates.
 * 
 * @param file_name File needed to the final print
 * @param sort_criteria The sorting method
 * @param compare Element in comparison
 */
static void test_with_comparison_function(const char *file_name, int sort_criteria, int (*compare)(void*, void*)) {
  /* Variables for measuring time */ 
  struct timespec begin;

  /* Creating and loading array */
  begin = start_timer();
  OrderedArray *array = array_create(compare);
  load_array(file_name, array);
  printf(F_YELLOW "Time measured for loading: %.4f seconds.\n" ENDSTYLE, stop_timer(begin)); 

  /* Order array loaded */
  begin = start_timer();
  char *c = (sort_criteria == 1) ? "STRING" : ((sort_criteria == 2) ? "INTEGER" : "DOUBLE");
  printf("\nORDER ARRAY OF RECORDS BY %s\n", c);
  order_array(array,0,array_size(array)-1);
  printf("Sorting by %s COMPLETED!\n", c);
  printf(F_RED "Time measured for sorting: %.4f seconds.\n" ENDSTYLE, stop_timer(begin)); 

  /* Write sorted array into the file */ 
  begin = start_timer();
  write_array(array,file_name);
  free_array(array);
  printf(F_GREEN "Time measured for writing writing data to the file: %.4f seconds.\n\n\n\n\n" ENDSTYLE, stop_timer(begin)); 
}


int main(int argc, char const *argv[]) {
  if ((argc < 4) || (strcmp(argv[2],"0") != 0 && strcmp(argv[2],"1") != 0 && strcmp(argv[2],"2") != 0 && strcmp(argv[2],"3") != 0)
    || (strcmp(argv[3],"0") != 0 && strcmp(argv[3],"1") != 0)) {
    printf("Usage: ordered_array_main <file_name> <0 (all)|1 (string)|2 (int)|3 (double)> <0 (increasing)|1 (decreasing)>\n");
    exit(EXIT_FAILURE);
  }

  /* Selecting the order criteria */
  int criteria = atoi(argv[2]);
  int order = atoi(argv[3]);
  switch (criteria){

    /* Order by all criteria */ 
    case 0:
      if (order == 0){
        test_with_comparison_function(argv[1], 1, precedes_record_string_field_cr);
        test_with_comparison_function(argv[1], 2, precedes_record_int_field_cr);
        test_with_comparison_function(argv[1], 3, precedes_record_double_field_cr);
      }
      else{
        test_with_comparison_function(argv[1], 1, precedes_record_string_field_decr);
        test_with_comparison_function(argv[1], 2, precedes_record_int_field_decr);
        test_with_comparison_function(argv[1], 3, precedes_record_double_field_decr);
      }
      
      
      break;

    /* Order by string field */ 
    case 1:
      if (order == 0){
        test_with_comparison_function(argv[1], criteria, precedes_record_string_field_cr);
      }
      else{
        test_with_comparison_function(argv[1], criteria, precedes_record_string_field_decr);
      }
      break;

    /* Order by integer field */ 
    case 2:
      if (order == 0){
        test_with_comparison_function(argv[1], criteria, precedes_record_int_field_cr);
      }
      else{
        test_with_comparison_function(argv[1], criteria, precedes_record_int_field_decr);
      }
      break;

    /* Order by double field */ 
    case 3:
      if (order == 0){
        test_with_comparison_function(argv[1], criteria, precedes_record_double_field_cr);
      }
      else{
        test_with_comparison_function(argv[1], criteria, precedes_record_double_field_decr);
      }
      break;
    
    default:
      fprintf(stderr,"main: unable to select the sorting criteria");
      exit(EXIT_FAILURE);
      break;
  }

  return EXIT_SUCCESS;
}