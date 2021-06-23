/* Side library used to handle the lists of
the list of word suggested, for every word
read from a file to be corrected. We also
keep track the dictionary used to correct */ 
#include "common.h"
#include "word_list_utils.h"

/* Struct that registers the list of suggested
word list for every word read, based on the
dictionary inside */ 
typedef struct _edit_distancer{
  Word_list **w_lists; /* The word lists for every word corrected */ 
  int list_size; /* The number of words in the list */
  int list_capacity; /* The capacity of the list */
} Edit_distancer;

/* Initial list of word list capacity */ 
#define INITIAL_CAPACITY 2

/**
 * @brief Initialize edit_distancer struct, allocating initial
 * space for the list of lists and loading the dictionary
 * 
 * @param dict_name The file name of the dictionary
 * @return The new fresh struct
 */
Edit_distancer *edit_distancer_create();

/**
 * @brief Returns the number of lists actually
 * registered
 * 
 * @param ed_distancer the Edit_distancer struct
 * @return The array size
 */
int edit_distancer_size(Edit_distancer *ed_distancer);

/**
 * @brief Adds a new word list for a new word into
 * the array
 * 
 * @param ed_distancer The Edit_distancer struct
 * @param new_w_list The new word list to be added
 */
void edit_distancer_add_word_list(Edit_distancer *ed_distancer, Word_list *new_w_list);

/**
 * @brief Retrieves a word list from the list, at a specific index
 * 
 * @param ed_distancer The Edit_distancer struct
 * @param i The index
 * @return The word list at index i 
 */
Word_list *edit_distancer_word_list_get(Edit_distancer *ed_distancer, int i);

/**
 * @brief Deallocating the struct and its content
 * 
 * @param ed_distancer The Edit_distancer struct
 */
void edit_distancer_deallocate(Edit_distancer *ed_distancer);