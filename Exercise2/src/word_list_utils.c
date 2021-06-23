#include "word_list_utils.h"

Word_list *word_list_create(char *init_word, int init_edit_distance) {

  /* Allocating space for the struct */ 
  Word_list *sugg_str = (Word_list *) malloc(sizeof(Word_list));
  if(sugg_str == NULL) {
    fprintf(stderr, "word_list_create: unable tu alloc memory for the edit distancer");
    exit(EXIT_FAILURE);
  }

  /* Allocating initial space for the words list */ 
  sugg_str->words_list = (char **) calloc(INITIAL_CAPACITY, sizeof(char *));
  if(sugg_str->words_list == NULL) {
    fprintf(stderr, "word_list_create: uneble to create memory for the words list");
    exit(EXIT_FAILURE);
  }

  /* Initializing the other struct attributes */ 
  sugg_str->src_word = (char *) calloc(strlen(init_word), sizeof(char));
  strcpy(sugg_str->src_word,init_word);
  sugg_str->list_size = 0;
  sugg_str->list_capacity = INITIAL_CAPACITY;
  sugg_str->edit_distance = init_edit_distance;
  sugg_str->time = 0;
  return sugg_str;
}

int word_list_size(Word_list *sugg_str) {
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_size: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  return sugg_str->list_size;
}

void word_list_add_word(Word_list *sugg_str, char *new_word) {
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_add_word: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (new_word == NULL) {
    fprintf(stderr, "word_list_add_word: the suggested word parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  /* Check if the actual words list size excedes its capacity */ 
  if (sugg_str->list_size >= sugg_str->list_capacity) {
    sugg_str->list_capacity = 2 + sugg_str->list_capacity; /* Doubling the capacity */ 
    sugg_str->words_list = (char **) realloc(sugg_str->words_list, (size_t) sugg_str->list_capacity * sizeof(char *));
    if (sugg_str->words_list == NULL) {
      fprintf(stderr,"word_list_add_word: unable to reallocate memory to add the new suggested word");
      exit(EXIT_FAILURE);
    }
  }

  /* Insert the new word */ 
  sugg_str->words_list[sugg_str->list_size] = (char *) calloc(strlen(new_word), sizeof(char));
  strcpy(sugg_str->words_list[sugg_str->list_size],new_word);
  sugg_str->list_size++;
}

char *word_list_word_get(Word_list *sugg_str, int i) {
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_word_get: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= sugg_str->list_size) {
    fprintf(stderr, "word_list_word_get: Index %d is out of the words list bounds", i);
    exit(EXIT_FAILURE);
  }

  return sugg_str->words_list[i];
}

char *word_list_src_word_get(Word_list *sugg_str){
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_src_word_get: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  return sugg_str->src_word;
}

int word_list_ed_dist_get(Word_list *sugg_str){
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_ed_dist_get: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  return sugg_str->edit_distance;
}

double word_list_time_get(Word_list *sugg_str){
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_time_get: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  return sugg_str->time;
}

void word_list_time_set(Word_list *sugg_str, double t){
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_time_set: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (t <= 0) {
    fprintf(stderr, "word_list_time_set: t parameter cannot be <= 0");
    exit(EXIT_FAILURE);
  }

  sugg_str->time = t;
}

void word_list_deallocate(Word_list *sugg_str) {
  if (sugg_str == NULL) {
    fprintf(stderr, "word_list_deallocate: sugg_str parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(sugg_str->words_list);
  free(sugg_str->src_word);
  free(sugg_str);
}
