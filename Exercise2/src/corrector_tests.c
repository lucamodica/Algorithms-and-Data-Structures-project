#include "unity.h"
#include "common.h"
#include "edit_distance.h"

/* ***Test suite for ordered array data structure and algorithms*** */ 

/* TEST1: both the strings is empty  */ 
static void test_ed_dist_both_empty() {
  char *s1 = "";
  char *s2 = "";
  TEST_ASSERT_EQUAL_INT(0, edit_distance(s1,s2));
  TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(s1,s2));
}

/* TEST2: first string is empty */ 
static void test_ed_dist_first_empty() {
  char *s1 = "";
  char *s2 = "Halo";
  TEST_ASSERT_EQUAL_INT(4, edit_distance(s1,s2));
  TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn(s1,s2));
}

/* TEST3: second string is empty */ 
static void test_ed_dist_second_empty() {
  char *s1 = "Halo";
  char *s2 = "";
  TEST_ASSERT_EQUAL_INT(4, edit_distance(s1,s2));
  TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn(s1,s2));
}

/* TEST4: the strings are the same string */ 
static void test_ed_dist_same_string() {
  char *s1 = "Halo";
  char *s2 = "Halo";
  TEST_ASSERT_EQUAL_INT(0, edit_distance(s1,s2));
  TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(s1,s2));
}

/* TEST5: testing edit distace = 1 */ 
static void test_ed_dist_1() {
  char *s1 = "Halo";
  char *s2 = "Hlo";
  TEST_ASSERT_EQUAL_INT(1, edit_distance(s1,s2));

  s1 = "Halo";
  s2 = "Haalo";
  TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn(s1,s2));
}

/* TEST6: testing edit distace = 2 */ 
static void test_ed_dist_2() {
  char *s1 = "Halo";
  char *s2 = "Ho";
  TEST_ASSERT_EQUAL_INT(2, edit_distance(s1,s2));

  s1 = "Halo";
  s2 = "Haaloo";
  TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn(s1,s2));
  
}

/* TEST7: testing edit distace = 3 */ 
static void test_ed_dist_3() {
  char *s1 = "Halo";
  char *s2 = "o";
  TEST_ASSERT_EQUAL_INT(3, edit_distance(s1,s2));

  s1 = "Hl";
  s2 = "Haloo";
  TEST_ASSERT_EQUAL_INT(3, edit_distance_dyn(s1,s2));
  
}

/* TEST8: palindrome strings */ 
static void test_edit_dist_palindrome_strings() {
  char *s1 = "Anna";
  char *s2 = "Anna";
  TEST_ASSERT_EQUAL_INT(0, edit_distance(s1,s2));

  s1 = "Otto";
  s2 = "Otto";
  TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(s1,s2));
  
}

/* TEST9: inverted strings */ 
static void test_edit_dist_inverted_strings() {
  char *s1 = "Halo";
  char *s2 = "olaH";
  TEST_ASSERT_EQUAL_INT(6, edit_distance(s1,s2));

  s1 = "Drago";
  s2 = "ogarD";
  TEST_ASSERT_EQUAL_INT(8, edit_distance_dyn(s1,s2)); 

}

/* TEST10: generic strings */ 
static void generic_test() {
  char *s1 = "Anna";
  char *s2 = "Otto";
  TEST_ASSERT_EQUAL_INT(8, edit_distance(s1,s2));

  s1 = "Uni";
  s2 = "Stress";
  TEST_ASSERT_EQUAL_INT(9, edit_distance_dyn(s1,s2)); 
}



int main() {
  UNITY_BEGIN();
  RUN_TEST(test_ed_dist_both_empty);
  RUN_TEST(test_ed_dist_first_empty);
  RUN_TEST(test_ed_dist_second_empty);
  RUN_TEST(test_ed_dist_same_string);
  RUN_TEST(test_ed_dist_1);
  RUN_TEST(test_ed_dist_2);
  RUN_TEST(test_ed_dist_3);
  RUN_TEST(test_edit_dist_palindrome_strings);
  RUN_TEST(test_edit_dist_inverted_strings);
  RUN_TEST(generic_test);
  return UNITY_END();
}