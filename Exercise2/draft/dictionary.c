#include "edit-distance.h"
#include <time.h>

/* Buffer size for reading a data file */ 
#define BUFFER_SIZE 1024

/* Styiling text */
#define F_YELLOW "\x1b[33m" 
#define F_RED "\x1b[31m"
#define F_GREEN "\x1b[32m"
#define ENDSTYLE "\x1b[0m"

typedef struct _edit_distancer{
  char *str;
  int edit_distance;
} Edit_distancer;


/* Function that loads file, and allocates the memory needed */
static Edit_distancer *dictionary_search(char *dict_name, char *string) {
  char buffer[BUFFER_SIZE];
  FILE *fp;
  int curr_edit_dist;

  /* Struct to register the string and its edit distance */ 
  Edit_distancer *sugg_str = (Edit_distancer *) malloc(sizeof(Edit_distancer));
  sugg_str->edit_distance = __INT_MAX__;
  sugg_str->str = (char *) calloc(BUFFER_SIZE, sizeof(char));

  printf("\nOpen dictionary...\n");
  fp = fopen(dict_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the dictionary file");
    exit(EXIT_FAILURE);
  }
  
  while ( (fgets(buffer, BUFFER_SIZE, fp) != NULL) && (sugg_str->edit_distance != 0) ){
    if (buffer != NULL){
      buffer[strcspn(buffer, "\n")] = 0;
      curr_edit_dist = edit_distance_dyn(buffer,string);

      if (curr_edit_dist < sugg_str->edit_distance){
        strcpy(sugg_str->str,buffer);
        sugg_str->edit_distance = curr_edit_dist;
      }
    }

    memset(buffer,0,BUFFER_SIZE);
  }
  fclose(fp);

  return sugg_str;
}


int main(int argc, char const *argv[]){
  if (argc != 2){
    printf("Usage: ./k <string>\n");
    exit(EXIT_FAILURE);
  }

  /* Variables for measuring time */ 
  struct timespec begin, end;
  long seconds, nanoseconds;
  double elapsed;

  char *str = (char *) argv[1];

  seconds = 0;
  nanoseconds = 0;
  elapsed = 0;
  clock_gettime(CLOCK_REALTIME, &begin);
  Edit_distancer *sugg_str = dictionary_search("../dictionary.txt",str);
  clock_gettime(CLOCK_REALTIME, &end);
  seconds = end.tv_sec - begin.tv_sec;
  nanoseconds = end.tv_nsec - begin.tv_nsec;
  elapsed = (double) seconds + (double) nanoseconds*1e-9;
  
  printf("\nWord inserted: \" %s \", suggested word from dictionary: \" %s \"(with edit distance: %d)\n\n", str, sugg_str->str, sugg_str->edit_distance);
  printf(F_RED "Time measured for finding: %.5f seconds.\n" ENDSTYLE, elapsed);
}