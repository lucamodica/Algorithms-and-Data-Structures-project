#include "edit_distance.h"

/**
 * @brief Compute the minium between 2 numbers 
 * 
 * @param n1 The first number
 * @param n2 The second number
 * @return The minium between n1 and n2
 */
static int min(int n1, int n2){
  if (n1 < n2){
    return n1;
  }
  return n2;
}

/**
 * @brief Incrementing the pointer of a char * (string) variable 
 * passed as parameter to ignore its first character
 * 
 * @param string The string for which we want to ignore the 
 * first character
 * @return The parameter string ignoring its first character
 */
static char *rest(char *string){
  return string + 1;
}

/**
 * @brief Internal part of the dynamic version of the edit distance,
 * which do the majority part of the work checking if a specific
 * recursion is not computed in a specific matrix cell. 
 * If is true, recursions will be excecuted in the same way as the
 * classical recursion version of the edit distance function.
 * Otherwise, the result is immediatly returned
 * 
 * @param str1 The destination string
 * @param str2 the src string
 * @param n The row index of the matrix. The number
 * of rows of the matrix will be the str1 length
 * @param m The cloumn index of the matrix. The number
 * of rows of the matrix will be the str2 length
 * @param calc The integer matrix himself used to apply
 * the memoization tecnique
 * @return The edit distance calculated 
 */
static int _edit_distance_dyn(char *str1, char *str2, int n, int m, int **calc){

  /* If the counter the for first string arrives to the
  strlen(str1), the number of remaining char of the second 
  string will be returned */ 
  if (n == (int) strlen(str1)){
    return (int) strlen(str2) - m;
  }
 
  /* If the counter the for second string arrives to the
  strlen(str2), the number of remaining char of the first 
  string will be returned */ 
  if (m == (int) strlen(str2)){
    return (int) strlen(str1) - n;
  }
  
  /* If the value is not computed yet, we proceed in the same way
  of the recursive version: we calculate the edit distance of the 3
  possible values and then we return the minium one, also storing it into
  the right cell of the matrix */
  if(calc[n][m] == 0){
    int d_noop = (str1[n] == str2[m]) ? _edit_distance_dyn(str1, str2, n + 1, m + 1, calc) : __INT_MAX__;
    int d_canc = (calc[n][m + 1] == 0) ? (calc[n][m + 1] = 1 + _edit_distance_dyn(str1, str2, n, m + 1, calc)) : calc[n][m + 1];
    int d_ins = (calc[n + 1][m] == 0) ? (calc[n + 1][m] = 1 + _edit_distance_dyn(str1, str2, n + 1, m, calc)) : calc[n + 1][m];

    /* Memorize the value computed */
    calc[n][m] = min(d_noop, min(d_canc, d_ins));
  }

  return calc[n][m];
}



int edit_distance_dyn(char *str1, char *str2){

  /* If first string is empty, the only option is to
  insert all characters of second string into first */
  if (strlen(str1) == 0){
    return (int) strlen(str2);
  }

  /* If second string is empty, the only option is to
  remove all characters of first string */
  if (strlen(str2) == 0){
    return (int) strlen(str1);
  }

  /* Creation of a matrix that stored every compute already 
  done in the edit_distance recursive calls */ 
  int **calc = (int **) calloc(strlen(str1) + 1,sizeof(int *));
  for (int i = 0; i < (int) strlen(str1) + 1; i++){
    calc[i] = (int *) calloc(strlen(str2) + 1,sizeof(int));
    memset(calc[i],0,strlen(str2) + 1);
  }

  /* Compute the edit distance using memoization */ 
  int ed_dist = _edit_distance_dyn(str1, str2, 0, 0, calc);

  /* Deallocating the matrix */ 
  for (int i = 0; i < (int) strlen(str1) + 1; i++){
    free(calc[i]);
  }
  free(calc);

  return ed_dist;

}


int edit_distance(char *str1, char *str2){

  /* Variables to store the possible 3 values
  of the edit distance */ 
  int d_noop, d_canc, d_ins;

  /* If first string is empty, the only option is to
  insert all characters of second string into first */
  if (strlen(str1) == 0){
    return (int) strlen(str2);
  }

  /* If second string is empty, the only option is to
  remove all characters of first string */
  if (strlen(str2) == 0){
    return (int) strlen(str1);
  }

  d_noop = (str1[0] == str2[0]) ? edit_distance(rest(str1), rest(str2)) : __INT_MAX__;
  d_canc = 1 + edit_distance(str1, rest(str2));
  d_ins = 1 + edit_distance(rest(str1), str2);

  /* If first characters are the same, consider all three
  operations on last character of first string,
  recursively compute minimum cost for all three
  operations and take minimum of three values. */
  return min(d_noop, min(d_canc,d_ins));
}

