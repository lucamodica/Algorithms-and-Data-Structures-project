#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compute the number of operations needed to convert str2
in str1 (cancellation/insertion) */
int edit_distance(char *str1, char *str2);

/* Dynamic version of edit_distance() func */
int edit_distance_dyn(char *str1, char *str2);