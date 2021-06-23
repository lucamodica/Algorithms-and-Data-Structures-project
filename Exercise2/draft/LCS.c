#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int _LCS(char* str1, char* str2, int **calc, int r, int c){
  
  /* Computing the table */ 
  for (int i = 1; i < r; i++){
    for (int j = 1; j < c; j++){
      
      /* Case ↖ */ 
      if(str1[i-1] == str2[j-1]){
        calc[i][j] = calc[i-1][j-1] + 1;
      }
      else{
        /* Case ⬆ */ 
        if(calc[i-1][j] >= calc[i][j-1]){
          calc[i][j] = calc[i-1][j];
        }
        /* Case ⬅ */ 
        else{
          calc[i][j] = calc[i][j-1];
        }
      }

    }
  }

  

  return calc[r-1][c-1];
}


int LCS(char* str1, char* str2){

  if (strcmp(str1,str2) == 0){
    return (int) strlen(str1);
  }
  
  int r = strlen(str1) + 1;
  int c = strlen(str2) + 1;

  int **calc = (int **) calloc(r,sizeof(int *));
  for (int i = 0; i < r; i++){
    calc[i] = (int *) calloc(c,sizeof(int));
    memset(calc[i],0,c);
  }

  int res = _LCS(str1, str2, calc, r, c);

  for (int i = 0; i < r; i++){
    free(calc[i]);
  }
  free(calc);

  return res;
}

int main(int argc, const char *argv[]){
  if(argc != 3){
      printf("\n Usage: ./LCS <string1> <string2>\n");
      exit(EXIT_FAILURE);
  }

  char *s1 = (char *) argv[1];
  char *s2 = (char *) argv[2];
  int len_LCS = LCS(s1,s2);
  printf("\nlen_LCS(%s, %s) = %d\n", s1, s2, len_LCS);

  exit(EXIT_SUCCESS);
}