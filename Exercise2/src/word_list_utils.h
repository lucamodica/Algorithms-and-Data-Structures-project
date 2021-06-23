/* Side library used to handle the dynamic list of the
words suggested from the dictionary in the main file */ 
#include "common.h"

/* Struct that register suggested words, 
with the its edit distance */ 
typedef struct _word_list{
  char **words_list; /* The words list */ 
  char *src_word; /* The word from which we compute the edit distance */ 
  int list_size; /* The number of words in the list */
  int list_capacity; /* The capacity of the list */ 
  int edit_distance; /* The edit distance of the words in the list */ 
  double time; /* time measured to compute the word list */ 
} Word_list;

/* Initial suggested word list capacity */ 
#define INITIAL_CAPACITY 2


/**
 * @brief Initializing the struct, allocating a starting space
 * for the list and a starting values
 * 
 * @param src_word The word from which we compute the edit distance
 * @param init_edit_distance The initial edit_distance value
 * we want to allocate
 * @return A new fresh Word_list struct
 */
Word_list *word_list_create(char *src_word, int init_edit_distance);

/**
 * @brief Compute the actual size of the list of the parameter
 * strucy
 * 
 * @param sugg_str The Word_list struct 
 * @return The list size
 */
int word_list_size(Word_list *sugg_str);

/**
 * @brief Add a new words to the suggesting list
 * 
 * @param sugg_str The Word_list struct
 * @param new_word The new word to be added
 */
void word_list_add_word(Word_list *sugg_str, char *new_word);

/**
 * @brief Retrieving a word from the the suggesting list of
 * a specific index
 * 
 * @param sugg_str The Word_list struct
 * @param i The index in which we are interested
 * @return The word at index i
 */
char *word_list_word_get(Word_list *sugg_str, int i);

/**
 * @brief Retrieve the source word from which we compute
 * the word list
 * 
 * @param sugg_str The Word_list struct
 * @return The src word
 */
char *word_list_src_word_get(Word_list *sugg_str);

/**
 * @brief Retrieve the word list edit distance
 * 
 * @param sugg_str The Word_list struct
 * @return The word list edit distance
 */
int word_list_ed_dist_get(Word_list *sugg_str);

/**
 * @brief Retrieving the time taken to create
 * the word list
 * 
 * @param sugg_str The Word_list struct
 * @return the time measured 
 */
double word_list_time_get(Word_list *sugg_str);

/**
 * @brief Set the time taken to create the word
 * list
 * 
 * @param sugg_str The Word_list struct
 * @param t The time we want to set
 */
void word_list_time_set(Word_list *sugg_str, double t);

/**
 * @brief Deallocate the word list and then the Word_list
 * struct itsself 
 * 
 * @param sugg_str The struct we want to deallocate
 */
void word_list_deallocate(Word_list *sugg_str);