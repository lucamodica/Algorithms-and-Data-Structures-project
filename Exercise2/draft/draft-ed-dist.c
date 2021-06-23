#include "draft-ed-dist.h"


//returns the smaller number between n1, n2
static int min(int n1, int n2){
  if (n1 < n2){
    return n1;
  }
  return n2;
}

/*static char *rest_fake(char *string)
{
  char arr[strlen(string)];
  strcpy(arr,string);
  char sup = arr-1;
  printf("%s",sup[0]);
  return sup;
}*/

// ERROR returns char* without the first char
static char *rest(char *string){
  return string + 1;
}

static char *rest1(char *src){
    // get the length of the destination string
    int len = strlen(src) - 1;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = 1; i < strlen(src) && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}

/*static char* edit_distance_v1(char* word1, char* word2) {
  printf("\n--Edit Zone--\n");
  printf("Recived \"%s\" and \"%s\" from main\n",word1,word2);
  char* rest_return = rest(word1);
  printf("Ending of edit_distance zone, i'm printing the word %s, %s 3====D\n\n",rest_return,word1);
  return word1;
}*/





/* Another edit_distance version eheh */ 
/* IT WORKS */ 
int edit_distance(char *str1, char *str2){

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

int editDistDyn(char * str1, char * str2, int m, int n, int **dp){

  int noop, canc, ins;

  // If first string is empty, the only option is to
  // insert all characters of second string into first
  if (m == 0)
      return n;
 
  // If second string is empty, the only option is to
  // remove all characters of first string
  if (n == 0)
      return m;
 
  // if the recursive call has been
  // called previously, then return
  // the stored value that was calculated
  // previously
  if (dp[m - 1][n - 1] != -1)
      return dp[m - 1][n - 1];
 
  // If last characters of two strings are same, nothing
  // much to do. Ignore last characters and get count for
  // remaining strings.
 
  // Store the returned value at dp[m-1][n-1]
  // considering 1-based indexing
  if (str1[m - 1] == str2[n - 1])
      return dp[m - 1][n - 1] = editDistDyn(str1, str2, m - 1, n - 1, dp);
 
  // If last characters are not same, consider all three
  // operations on last character of first string, recursively
  // compute minimum cost for all three operations and take
  // minimum of three values.

  
 
  // Store the returned value at dp[m-1][n-1]
  // considering 1-based indexing
  return dp[m - 1][n - 1] = 1 + min(editDistDyn(str1, str2, m, n - 1, dp), // Insert
                                    min(editDistDyn(str1, str2, m - 1, n, dp), // Remove
                                    editDistDyn(str1, str2, m - 1, n - 1, dp)) // Replace
                                    );
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
  //return editDistDyn(str1, str2, strlen(str1), strlen(str2), calc);
}




//Edit-distance using rest() function
//WARNING: SEGMENTATION FAULT!
static int edit_distance_v1(char *str1, char *str2)
{

  /* If first string is empty, the only option is to
  insert all characters of second string into first */
  if (strlen(str1) == 0)
  {
    return strlen(str2);
  }

  /* If second string is empty, the only option is to
  remove all characters of first string */
  if (strlen(str2) == 0)
  {
    return strlen(str1);
  }

  /* If last characters of two strings are same, ignore last characters,
  move on and count the remaining chars. */
  if (str1[0] == str2[0])
  {
    return edit_distance(rest(str1), rest(str2));
  }

  /* If last characters are not same, consider all three
  operations on last character of first string,
  recursively compute minimum cost for all three
  operations and take minimum of three values. */

  return 1 + min(edit_distance(str1, rest(str2)) /*Insert*/, min(edit_distance(rest(str1), str2), /* Remove */ edit_distance(rest(str1), rest(str2)) /* Noop */));
}

//Edit-distance without rest() function
static int editDist(char *str1, char *str2, int m, int n)
{

  /* If first string is empty, the only option is to
  insert all characters of second string into first */
  if (m == 0)
    return n;

  /* If second string is empty, the only option is to
  remove all characters of first string */
  if (n == 0)
    return m;

  /* If last characters of two strings are same, ignore last characters,
  move on and count the remaining chars. */
  if (str1[m - 1] == str2[n - 1])
    return editDist(str1, str2, m - 1, n - 1);

  /* If last characters are not same, consider all three
  operations on last character of first string,
  recursively compute minimum cost for all three
  operations and take minimum of three values. */
  return 1 + min(editDist(str1, str2, m, n - 1) /*Insert*/, min(editDist(str1, str2, m - 1, n) /* Remove */, editDist(str1, str2, m - 1, n - 1)/* Noop */));
}



int main(int argc, char const *argv[]){
  if (argc < 3){
    printf("Usage: k <string1> <string2>\n");
    exit(EXIT_FAILURE);
  }
  char *str1 = (char *) argv[1];
  char *str2 = (char *) argv[2];
  
  printf("\n(RECURSIVE VERSION) Vecchia parola: %s, nuova parola: %s.\n\nEdit distance: %d !\n\n", str2, str1, edit_distance(str1, str2));
  printf("\n(DYNAMIC VERSION) Vecchia parola: %s, nuova parola: %s.\n\nEdit distance: %d !\n\n", str2, str1, edit_distance_dyn(str1, str2));
  //printf("\nVecchia parola: %s, nuova parola: %s.\n\nEdit distance: %d !\n\n", str1, str2, editDist(str1, str2, strlen(str1), strlen(str2)));
}