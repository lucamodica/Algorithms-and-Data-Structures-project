#include "edit_distancer_utils.h"

Edit_distancer *edit_distancer_create(){
  /* Allocating space for the struct */ 
  Edit_distancer *ed_distancer = (Edit_distancer *) malloc(sizeof(Edit_distancer));
  if(ed_distancer == NULL) {
    fprintf(stderr, "edit_distancer_create: unable tu alloc memory for the edit distancer");
    exit(EXIT_FAILURE);
  }

  /* Allocating initial space for the list of word list */ 
  ed_distancer->w_lists = (Word_list **) calloc(INITIAL_CAPACITY, sizeof(Word_list *));
  if(ed_distancer->w_lists == NULL) {
    fprintf(stderr, "edit_distancer_create: uneble to create memory for the words list");
    exit(EXIT_FAILURE);
  }

  /* Initializing the other struct attributes */ 
  ed_distancer->list_size = 0;
  ed_distancer->list_capacity = INITIAL_CAPACITY;
  return ed_distancer;
}

int edit_distancer_size(Edit_distancer *ed_distancer){
  if (ed_distancer == NULL) {
    fprintf(stderr, "edit_distancer_size: ed_distancer parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  return ed_distancer->list_size;
}

void edit_distancer_add_word_list(Edit_distancer *ed_distancer, Word_list *new_w_list){
  if (ed_distancer == NULL) {
    fprintf(stderr, "edit_distancer_add_word_list: ed_distancer parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (new_w_list == NULL) {
    fprintf(stderr, "edit_distancer_add_word_list: the new list parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  /* Check if the actual words list size excedes its capacity */ 
  if (ed_distancer->list_size >= ed_distancer->list_capacity) {
    ed_distancer->list_capacity = 2 + ed_distancer->list_capacity; /* Doubling the capacity */ 
    ed_distancer->w_lists = (Word_list **) realloc(ed_distancer->w_lists, (size_t) ed_distancer->list_capacity * sizeof(Word_list *));
    if (ed_distancer->w_lists == NULL) {
      fprintf(stderr,"edit_distancer_add_word_list: unable to reallocate memory to add the new list");
      exit(EXIT_FAILURE);
    }
  }

  /* Insert the new list */ 
  ed_distancer->w_lists[ed_distancer->list_size] = (Word_list *) malloc(sizeof(Word_list));
  ed_distancer->w_lists[ed_distancer->list_size] = new_w_list;
  ed_distancer->list_size++;
}

Word_list *edit_distancer_word_list_get(Edit_distancer *ed_distancer, int i){
  if (ed_distancer == NULL) {
    fprintf(stderr, "edit_distancer_word_list_get: ed_distancer parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ed_distancer->list_size) {
    fprintf(stderr, "edit_distancer_word_list_get: Index %d is out of the list of words list bounds", i);
    exit(EXIT_FAILURE);
  }

  return ed_distancer->w_lists[i];
}

void edit_distancer_deallocate(Edit_distancer *ed_distancer){
  if (ed_distancer == NULL) {
    fprintf(stderr, "edit_distancer_deallocate: ed_distancer parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < ed_distancer->list_size; i++){
    word_list_deallocate(edit_distancer_word_list_get(ed_distancer,i));
  }
  
  free(ed_distancer->w_lists);
  free(ed_distancer);
}