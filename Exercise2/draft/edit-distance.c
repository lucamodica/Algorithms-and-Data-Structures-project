#include "edit-distance.h"

/* Returns the smaller number between n1, n2 */ 
static int min(int n1, int n2)
{
  if (n1 < n2)
  {
    return n1;
  }
  return n2;
}

/* Returns the string without its first character */ 
static char *rest(char *string){
  return string + 1;
}

int edit_distance(char *str1, char *str2){

  /* Variables to store the possible 3 values
  of the edit distance */ 
  int d_noop, d_canc, d_ins;

  /* If first string is empty, the only option is to
  insert all characters of second string into first */
  if (strlen(str1) == 0){
    return strlen(str2);
  }

  /* If second string is empty, the only option is to
  remove all characters of first string */
  if (strlen(str2) == 0){
    return strlen(str1);
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

/* Internal part of edit_distance_dyn */ 
static int _edit_distance_dyn(char *str1, char *str2, int n, int m, int **calc){

  /* Variables to store the possible 3 values
  of the edit distance */ 
  int d_noop, d_canc, d_ins;

  /* If the counter the for first string arrives to the
  strlen(str1), the number of remaining char of the second 
  string will be returned */ 
  if (n == strlen(str1)){
    return strlen(str2) - m;
  }
 
  /* If the counter the for second string arrives to the
  strlen(str2), the number of remaining char of the first 
  string will be returned */ 
  if (m == strlen(str2)){
    return strlen(str1) - n;
  }
  
  /* Check if the current recursive call has been done
  previously: if it's the case, we return the value 
  already computed */ 
  if(calc[n][m] != 0){
    return calc[n][m];
  }

  /* If instead the value is not computed yet, we proceed in the same way
  of the recursive version: we calculate the edit distance of the 3
  possible values and then we return the minium one, also storing it into
  the right cell of the matrix */
  d_noop = (str1[n] == str2[m]) ? _edit_distance_dyn(str1, str2, n + 1, m + 1, calc) : __INT_MAX__;
  d_canc = 1 + _edit_distance_dyn(str1, str2, n, m + 1, calc);
  d_ins = 1 + _edit_distance_dyn(str1, str2, n + 1, m, calc);

  return calc[n][m] = min(d_noop, min(d_canc,d_ins));
}

int edit_distance_dyn(char *str1, char *str2){

  /* If first string is empty, the only option is to
  insert all characters of second string into first */
  if (strlen(str1) == 0){
    return strlen(str2);
  }

  /* If second string is empty, the only option is to
  remove all characters of first string */
  if (strlen(str2) == 0){
    return strlen(str1);
  }

  /* Using memoization, We create a matrix that stored every
  compute already done in the edit_distance recursive calls */ 
  int **calc = (int **) calloc(strlen(str1),sizeof(int *));
  for (int i = 0; i < strlen(str1); i++){
    calc[i] = (int *) calloc(strlen(str2),sizeof(int));
    memset(calc[i],0,strlen(str2));
  }

  return _edit_distance_dyn(str1, str2, 0, 0, calc);
}

