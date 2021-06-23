/* The core library of the application. This include 2 different version (recursive 
and dynamic) of the same fucntion, which compute the edit distance to transform the 
second string to the first one using charcter insertion and deletion as operation
available. */ 
#include "common.h"

/**
 * @brief The recursive version of the function. Computes the edit distance 
 * needed to transform the second string into the first one using charcter 
 * insertion and deletion as operation available.
 * 
 * @param str1 The destination string
 * @param str2 The src string
 * @return The edit distance itself, that is the number of insertion/deletion
 * needed to transform str2 into str1.
 */
int edit_distance(char *str1, char *str2);

/**
 * @brief The dynamic version of the function. Computes the edit distance 
 * in the same way as the classical recursive one, but with a key difference:
 * to avoid solving repeatedly the same problems during recursion, we use the
 * memoization technique, which consists of storing a value in a matrix and
 * retrieving it in case that specific problem was already solved.
 * 
 * @param str1 The destination string
 * @param str2 The src string
 * @return The edit distance itself, that is the number of insertion/deletion
 * needed to transform str2 into str1.
 */
int edit_distance_dyn(char *str1, char *str2);