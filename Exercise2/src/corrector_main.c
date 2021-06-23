#include "common.h"
#include "edit_distance.h"
#include "edit_distancer_utils.h"
#include <time.h>

/* Buffer size for reading a data file */ 
#define BUFFER_SIZE 1024

/* Number of words in the dictionary */
#define DICT_SIZE 661562

/* Styiling text */
#define F_YELLOW "\x1b[33m" /* Word read */ 
#define F_RED "\x1b[31m" /* Time measured */ 
#define F_GREEN "\x1b[32m" /* Result for every word */ 
#define ENDSTYLE "\x1b[0m" /* Reset color style */ 

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
 * @brief Load the dictionary
 * 
 * @param dict_name The dictionary name
 * @return The loades dictionary.
 */
static void load_dictionary(char *dict_name, char **dict){

  /* Buffer for reading the file */ 
  char buffer[BUFFER_SIZE];

  /* Opening the file */ 
  FILE *fp = fopen(dict_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "load_dictionary: unable to open the dictionary file");
    exit(EXIT_FAILURE);
  }

  /* Loading the dictionary */ 
  printf("Loading dictionary...\n");
  int i = 0;
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL){

    /* Adapting word read from the file */ 
    buffer[strcspn(buffer, "\n")] = 0;
    
    /* Inserting the word */ 
    dict[i] = (char *) calloc(strlen(buffer), sizeof(char));
    strcpy(dict[i],buffer);

    i++;    

  }
  printf("Dictionary loaded.\n\n\n");

  /* Closing the file */
  fclose(fp);
}

/**
 * @brief Creating a list of suggestions (the words is retrieved 
 * from a dictionary file) with minium edit_distance for the word 
 * passed as a parameter.
 * 
 * @param dict_name The of the dictionary file
 * @param string The word for which we want to compute suggestions 
 * @return A struct with the list of words suggested, and the
 * edit_distance of the list.
 */
static Word_list *dictionary_search(char **dict, char *string) {
  if (dict == NULL){
    fprintf(stderr, "dictionary_search: dict_name parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (string == NULL){
    fprintf(stderr, "dictionary_search: string parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  
  int curr_edit_dist; /* variable to keep track of the edit distance reading the file */ 
  struct timespec begin; /* Variables for starting the timer to measure time */ 

  /* Struct to register the suggested words
  list and its edit distance */ 
  Word_list *suggested_words = word_list_create(string,__INT_MAX__);
  
  /* Start the timer */
  begin = start_timer();

  /* searching for words */
  int i = 0;
  while (i < DICT_SIZE && (suggested_words->edit_distance != 0) ){

    /* Compute its edit distance with the input word */ 
    curr_edit_dist = edit_distance_dyn(dict[i],string);

    /* Case 1: the word has the same edit distance as
    the minium one recorded. The word will be added to
    the suggested words list */ 
    if (curr_edit_dist == suggested_words->edit_distance){
      word_list_add_word(suggested_words,dict[i]);
    }
    
    /* Case 2: the word has a lower edit distance than
    the minium one recorded. The suggested word list
    built until now will be deallocated, it will be 
    created a new one and it will be isnerted the new 
    word with a lower edit distnce */ 
    if (curr_edit_dist < suggested_words->edit_distance){
      word_list_deallocate(suggested_words);
      suggested_words = word_list_create(string,curr_edit_dist);
      word_list_add_word(suggested_words,dict[i]);
    }

    i++;
  }

  /* Stop the timer and save the time measured */
  word_list_time_set(suggested_words,stop_timer(begin));

  return suggested_words;
}

/**
 * @brief Printing all the words of a list built with the dictionary_search
 * function, complete with the edit distance registered.
 * 
 * @param sugg The struct containing the suggestions list and the
 * edit distance.
 */
static void print_suggestions(Edit_distancer *sugg){
  if (sugg == NULL){
    fprintf(stderr, "print_suggestions: dict_name parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  int answer = 1;
  do{
    printf("Do you also want to print suggestion with edit_distance = 0?\n");
    printf("[1] Yes\n");
    printf("[0] No\n");
    printf("> ");

    if (scanf("%d",&answer) == 0){
      printf("print_suggestions: failed to read the value of the answer.\n");
      exit(EXIT_FAILURE);
    }

    if((answer != 0) && (answer != 1)){
      printf("Invalid answer.\n\n");
    }
  }while((answer != 0) && (answer != 1));

  printf("\n");
  for (int i = 0; i < edit_distancer_size(sugg); i++){

    Word_list *l = edit_distancer_word_list_get(sugg,i);

    if(!(answer == 0 && word_list_ed_dist_get(l) == 0)){
      printf(F_YELLOW "Word: %11s" ENDSTYLE " | ", word_list_src_word_get(l));
      printf("[edit dist = %d] ", word_list_ed_dist_get(l));

      printf(F_GREEN "Suggested words: {");
      for (int j = 0; j < word_list_size(l); j++){
        printf("%s", word_list_word_get(l,j));
        if(j < word_list_size(l) - 1){
          printf(", ");
        }
      }
      printf("}\n" ENDSTYLE);
      printf(F_RED "(time measured: %.3fs)\n\n" ENDSTYLE, word_list_time_get(l));
    }
    
  }

  printf("\n\n");
}

/**
 * @brief Listing suggested words for every word read from
 * the file to be corrected.
 * 
 * @param txt_name The name of the file that needs to be corrected
 */
static void correct_me(const char *txt_name){
  if (txt_name == NULL){
    fprintf(stderr, "correct_me: string parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  char buffer[BUFFER_SIZE]; /* Buffer for reading the file */ 
  FILE *fp_txt; /* File handler for the file to be corrected */
  struct timespec begin; /* Variables for starting the timer to measure time */ 

  /* Struct to register the list of suggested word list */ 
  Edit_distancer *edit_distancer = edit_distancer_create();

  /* Open the file to be corrected */ 
  fp_txt = fopen(txt_name, "r");
  if (fp_txt == NULL) {
    fprintf(stderr, "correct_me: unable to open the file to be corected");
    exit(EXIT_FAILURE);
  }

  /* Loading dictionary */
  char *dictionary[DICT_SIZE];
  load_dictionary("dictionary.txt",dictionary);

  /* Start the timer */
  begin = start_timer();

  /* Read all the words inside the file to be corrected
  suggesting a list of words with minium edit distance 
  for each of them */ 
  printf("Correcting the file...\n");
  while (fscanf(fp_txt, "%s", buffer) != EOF){

    /* Adapting word read from the file */ 
    buffer[strcspn(buffer, "\n")] = 0;
    buffer[strcspn(buffer, ",")] = 0;
    buffer[strcspn(buffer, ".")] = 0;
    buffer[strcspn(buffer, ":")] = 0;

    /* Computing the list of suggested words from the dictionary */ 
    Word_list *suggested_words = dictionary_search(dictionary,buffer);

    /* Adding the word list to the edit distancer */ 
    edit_distancer_add_word_list(edit_distancer,suggested_words);

  }

  /* Closing the file */ 
  fclose(fp_txt);

  /* Print the measured time of the entire program */
  printf(F_GREEN "***Correction of %s, done!***\n" ENDSTYLE, txt_name);
  printf(F_RED "(Time measured for the whole correction: %.4f seconds)\n\n\n" ENDSTYLE, stop_timer(begin));

  /* Print all of the list of suggested words */
  print_suggestions(edit_distancer);

  /* Deallocating the edit distancer */ 
  edit_distancer_deallocate(edit_distancer);
}



int main(int argc, char const *argv[]){
  if (argc != 2){
    printf("Usage: ./main_corrector <file_to_be_corrected.txt>\n");
    exit(EXIT_FAILURE);
  }

  /* Starting the program */ 
  printf(F_YELLOW "\n***Correction of the file %s, started.***\n\n\n" ENDSTYLE, argv[1]);
  correct_me(argv[1]);

  return EXIT_SUCCESS;
}