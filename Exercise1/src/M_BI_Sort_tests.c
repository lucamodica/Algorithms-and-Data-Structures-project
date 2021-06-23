#include "unity.h"
#include "array_management.h"

/* ***Test suite for ordered array data structure and algorithms*** */ 

/* Struct used by the last test, for a generic array */ 
typedef struct _record {
  int index;
  char *string_field;
  int integer_field;
  double double_field;
} Record;

/* precedence relation used in tests for integer */ 
static int precedes_int(void *i1_p, void *i2_p) {
  if (i1_p == NULL) {
    fprintf(stderr, "precedes_int: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (i2_p == NULL) {
    fprintf(stderr, "precedes_int: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  int *int1_p = (int*)i1_p;
  int *int2_p = (int*)i2_p;
  return *int1_p > *int2_p;
}


/* precedence relations used in the last test for records
(the criteria is based on their integer_field field) */ 
static int precedes_record_int_field_cr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_cr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_cr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field > rec2_p->integer_field;
}
static int precedes_record_int_field_decr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_decr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field_decr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field < rec2_p->integer_field;
}

/* precedence relations used in the last test for records
(the criteria is based on their string_field field) */ 
static int precedes_record_string_field_cr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_string_cr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_string_cr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) > 0;
}
static int precedes_record_string_field_decr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_string_field_decr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_string_field_decr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

/* precedence relations used in the last test for records
(the criteria is based on their double_field field) */ 
static int precedes_record_double_field_cr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_cr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_cr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(rec1_p->double_field > rec2_p->double_field){
    return 1;
  } 
  else if(rec1_p->double_field == rec2_p->double_field){
    return 0;
  } 
  else {
    return -1;
  }
}
static int precedes_record_double_field_decr(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_decr: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_double_field_decr: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  
  if(rec1_p->double_field < rec2_p->double_field){
    return 1;
  } 
  else if(rec1_p->double_field == rec2_p->double_field){
    return 0;
  } 
  else {
    return -1;
  }
}



/* TEST1: empty array, test if is empty */ 
static void test_array_mbi_is_empty_zero_el() {
  OrderedArray *array_mbi_int = array_create(precedes_int);
  TEST_ASSERT_TRUE(is_array_empty(array_mbi_int));
  array_free_memory(array_mbi_int);
}

/* TEST2: array with 1 element, test if is empty */ 
static void test_array_mbi_is_empty_one_el() {
  int i = -12;
  OrderedArray *array_mbi_int = array_create(precedes_int);
  array_add(array_mbi_int, &i);
  TEST_ASSERT_FALSE(is_array_empty(array_mbi_int));
  array_free_memory(array_mbi_int);
}

/* TEST3: empty array, test if its size is 0 */ 
static void test_array_mbi_size_zero_el() {
  OrderedArray *array_mbi_int = array_create(precedes_int);
  TEST_ASSERT_EQUAL_INT(0, array_size(array_mbi_int));
  array_free_memory(array_mbi_int);
}

/* TEST4: array with 1 element, test if its size is 1 */ 
static void test_array_mbi_size_one_el() {
  int i1 = -12;
  OrderedArray *array_mbi_int = array_create(precedes_int);
  array_add(array_mbi_int, &i1);
  TEST_ASSERT_EQUAL_INT(1, array_size(array_mbi_int));
  array_free_memory(array_mbi_int);
}

/* TEST5: array with 2 element, test if its size is 2 */ 
static void test_array_mbi_size_two_el() {
  int i1 = -12;
  int i2 = 2;
  OrderedArray *array_mbi_int = array_create(precedes_int);
  array_add(array_mbi_int, &i1);
  array_add(array_mbi_int, &i2);
  TEST_ASSERT_EQUAL_INT(2, array_size(array_mbi_int));
  array_free_memory(array_mbi_int);
}

/* TEST6: array with 1 element, test if it's correctly added */ 
static void test_array_mbi_add_get_one_el() {
  int i1 = -12;
  OrderedArray *array_mbi_int = array_create(precedes_int);
  array_add(array_mbi_int, &i1);
  order_array(array_mbi_int, 0, array_size(array_mbi_int)-1);
  TEST_ASSERT_EQUAL_PTR(&i1, array_get(array_mbi_int, 0));
  array_free_memory(array_mbi_int);
}

/* TEST7: array with 3 element, test if it's sorted */ 
static void test_array_mbi_add_get_three_el() {
  int i1 = -12;
  int i2 = 0;
  int i3 = 4;
  int* exp_arr[] = {&i1, &i2, &i3};

  OrderedArray *array_mbi_int = array_create(precedes_int);
  array_add(array_mbi_int, &i1);
  array_add(array_mbi_int, &i2);
  array_add(array_mbi_int, &i3);
  order_array(array_mbi_int, 0, array_size(array_mbi_int)-1);

  int **act_arr = (int **) malloc(3*sizeof(int*));
  for (int i = 0; i < 3; i++) {
    act_arr[i] = (int*)array_get(array_mbi_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);
  free(act_arr);
  array_free_memory(array_mbi_int);
}

/* TEST8: generic array of 20 records, test if it's sorted by its integer_field field */ 
static void test_array_mbi_generic_array_by_integer() {
  Record r0 = {19356226, "oramai", 176798, 0.049583};
  Record r1 = {18669564, "nasce", 407381, 0.032548};
  Record r2 = {8198621, "Dite»", 728512, 0.108306};
  Record r3 = {16518263, "trista;", 753866, 0.071017};
  Record r4 = {11420871, "l'angel", 840531, 0.008983};
  Record r5 = {4799870, "Cianghella", 912847, 0.101348};
  Record r6 = {10712746, "convenne", 1224855, 0.024891};
  Record r7 = {17337294, "occhi", 1300318, 0.111894};
  Record r8 = {3889685, "virtù", 1660211, 0.087773};
  Record r9 = {13194096, "prese", 2161338, 0.130901};
  Record r10 = {16337190, "patto;", 2229852, 0.029045};
  Record r11 = {16121428, "buccia", 2873806, 0.089344};
  Record r12 = {17007052, "sinistra", 3460068, 0.129502};
  Record r13 = {11368335, "avea", 3486000, 0.047633};
  Record r14 = {13458372, "piccciola", 3502875, 0.009123};
  Record r15 = {14356882, "monte", 3518240, 0.109491};
  Record r16 = {11638755, "piacque", 3744375, 0.096175};
  Record r17 = {12975289, "picciola", 4096145, 0.067421};
  Record r18 = {18139264, "Beatrice", 4803662, 0.106408};
  Record r19 = {10090160, "vita", 4818350, 0.101326};
  Record* exp_arr_cr[] = {&r0, &r1, &r2, &r3, &r4, &r5, &r6, &r7, 
    &r8, &r9, &r10, &r11, &r12, &r13, &r14, &r15, &r16, &r17, &r18, &r19};
  Record* exp_arr_decr[] = {&r19, &r18, &r17, &r16, &r15, &r14, &r13, &r12, 
    &r11, &r10, &r9, &r8, &r7, &r6, &r5, &r4, &r3, &r2, &r1, &r0};

  OrderedArray *array_mbi_generic = array_create(precedes_record_int_field_cr);
  array_add(array_mbi_generic, &r19);
  array_add(array_mbi_generic, &r18);
  array_add(array_mbi_generic, &r17);
  array_add(array_mbi_generic, &r16);
  array_add(array_mbi_generic, &r15);
  array_add(array_mbi_generic, &r14);
  array_add(array_mbi_generic, &r13);
  array_add(array_mbi_generic, &r12);
  array_add(array_mbi_generic, &r11);
  array_add(array_mbi_generic, &r10);
  array_add(array_mbi_generic, &r9);
  array_add(array_mbi_generic, &r8);
  array_add(array_mbi_generic, &r7);
  array_add(array_mbi_generic, &r6);
  array_add(array_mbi_generic, &r5);
  array_add(array_mbi_generic, &r4);
  array_add(array_mbi_generic, &r3);
  array_add(array_mbi_generic, &r2);
  array_add(array_mbi_generic, &r1);
  array_add(array_mbi_generic, &r0);
  order_array(array_mbi_generic, 0, array_size(array_mbi_generic)-1);


  Record **act_arr = (Record **) malloc(20*sizeof(Record*));
  for (int i = 0; i < 20; i++) {
    act_arr[i] = (Record*)array_get(array_mbi_generic, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr_cr, act_arr, 20);

  array_mbi_generic->precedes = precedes_record_int_field_decr;
  order_array(array_mbi_generic, 0, array_size(array_mbi_generic)-1);
  act_arr = (Record **) malloc(20*sizeof(Record*));
  for (int i = 0; i < 20; i++) {
    act_arr[i] = (Record*)array_get(array_mbi_generic, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr_decr, act_arr, 20);

  free(act_arr);
  array_free_memory(array_mbi_generic);
}

/* TEST9: generic array of 20 records, test if it's sorted by its string_field field */ 
static void test_array_mbi_generic_array_by_string() {
  Record r0 = {18139264, "Beatrice", 4803662, 0.106408};
  Record r1 = {4799870, "Cianghella", 912847, 0.101348};
  Record r2 = {8198621, "Dite»", 728512, 0.108306};
  Record r3 = {11368335, "avea", 3486000, 0.047633};
  Record r4 = {16121428, "buccia", 2873806, 0.089344};
  Record r5 = {10712746, "convenne", 1224855, 0.024891};
  Record r6 = {11420871, "l'angel", 840531, 0.008983};
  Record r7 = {14356882, "monte", 3518240, 0.109491};
  Record r8 = {18669564, "nasce", 407381, 0.032548};
  Record r9 = {17337294, "occhi", 1300318, 0.111894};
  Record r10 = {19356226, "oramai", 176798, 0.049583};
  Record r11 = {16337190, "patto;", 2229852, 0.029045};
  Record r12 = {11638755, "piacque", 3744375, 0.096175};
  Record r13 = {13458372, "piccciola", 3502875, 0.009123};
  Record r14 = {12975289, "picciola", 4096145, 0.067421};
  Record r15 = {13194096, "prese", 2161338, 0.130901};
  Record r16 = {17007052, "sinistra", 3460068, 0.129502};
  Record r17 = {16518263, "trista;", 753866, 0.071017};
  Record r18 = {3889685, "virtù", 1660211, 0.087773};
  Record r19 = {10090160, "vita", 4818350, 0.101326};
  Record* exp_arr_cr[] = {&r0, &r1, &r2, &r3, &r4, &r5, &r6, &r7, 
    &r8, &r9, &r10, &r11, &r12, &r13, &r14, &r15, &r16, &r17, &r18, &r19};
  Record* exp_arr_decr[] = {&r19, &r18, &r17, &r16, &r15, &r14, &r13, &r12, 
    &r11, &r10, &r9, &r8, &r7, &r6, &r5, &r4, &r3, &r2, &r1, &r0};

  OrderedArray *array_mbi_generic = array_create(precedes_record_string_field_cr);
  array_add(array_mbi_generic, &r19);
  array_add(array_mbi_generic, &r18);
  array_add(array_mbi_generic, &r17);
  array_add(array_mbi_generic, &r16);
  array_add(array_mbi_generic, &r15);
  array_add(array_mbi_generic, &r14);
  array_add(array_mbi_generic, &r13);
  array_add(array_mbi_generic, &r12);
  array_add(array_mbi_generic, &r11);
  array_add(array_mbi_generic, &r10);
  array_add(array_mbi_generic, &r9);
  array_add(array_mbi_generic, &r8);
  array_add(array_mbi_generic, &r7);
  array_add(array_mbi_generic, &r6);
  array_add(array_mbi_generic, &r5);
  array_add(array_mbi_generic, &r4);
  array_add(array_mbi_generic, &r3);
  array_add(array_mbi_generic, &r2);
  array_add(array_mbi_generic, &r1);
  array_add(array_mbi_generic, &r0);
  order_array(array_mbi_generic, 0, array_size(array_mbi_generic)-1);


  Record **act_arr = (Record **) malloc(20*sizeof(Record*));
  for (int i = 0; i < 20; i++) {
    act_arr[i] = (Record*)array_get(array_mbi_generic, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr_cr, act_arr, 20);

  array_mbi_generic->precedes = precedes_record_string_field_decr;
  order_array(array_mbi_generic, 0, array_size(array_mbi_generic)-1);
  act_arr = (Record **) malloc(20*sizeof(Record*));
  for (int i = 0; i < 20; i++) {
    act_arr[i] = (Record*)array_get(array_mbi_generic, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr_decr, act_arr, 20);

  free(act_arr);
  array_free_memory(array_mbi_generic);
}

/* TEST10: generic array of 20 records, test if it's sorted by its double_field field */ 
static void test_array_mbi_generic_array_by_double() {
  Record r0 = {11420871, "l'angel", 840531, 0.008983};
  Record r1 = {13458372, "piccciola", 3502875, 0.009123};
  Record r2 = {10712746, "convenne", 1224855, 0.024891};
  Record r3 = {16337190, "patto;", 2229852, 0.029045};
  Record r4 = {18669564, "nasce", 407381, 0.032548};
  Record r5 = {11368335, "avea", 3486000, 0.047633};
  Record r6 = {19356226, "oramai", 176798, 0.049583};
  Record r7 = {12975289, "picciola", 4096145, 0.067421};
  Record r8 = {16518263, "trista;", 753866, 0.071017};
  Record r9 = {3889685, "virtù", 1660211, 0.087773};
  Record r10 = {16121428, "buccia", 2873806, 0.089344};
  Record r11 = {11638755, "piacque", 3744375, 0.096175};
  Record r12 = {10090160, "vita", 4818350, 0.101326};
  Record r13 = {4799870, "Cianghella", 912847, 0.101348};
  Record r14 = {18139264, "Beatrice", 4803662, 0.106408};
  Record r15 = {8198621, "Dite»", 728512, 0.108306};
  Record r16 = {14356882, "monte", 3518240, 0.109491};
  Record r17 = {17337294, "occhi", 1300318, 0.111894};
  Record r18 = {17007052, "sinistra", 3460068, 0.129502};
  Record r19 = {13194096, "prese", 2161338, 0.130901};
  Record* exp_arr[] = {&r0, &r1, &r2, &r3, &r4, &r5, &r6, &r7, 
    &r8, &r9, &r10, &r11, &r12, &r13, &r14, &r15, &r16, &r17, &r18, &r19};
  Record* exp_arr_decr[] = {&r19, &r18, &r17, &r16, &r15, &r14, &r13, &r12, 
    &r11, &r10, &r9, &r8, &r7, &r6, &r5, &r4, &r3, &r2, &r1, &r0};

  OrderedArray *array_mbi_generic = array_create(precedes_record_double_field_cr);
  array_add(array_mbi_generic, &r19);
  array_add(array_mbi_generic, &r18);
  array_add(array_mbi_generic, &r17);
  array_add(array_mbi_generic, &r16);
  array_add(array_mbi_generic, &r15);
  array_add(array_mbi_generic, &r14);
  array_add(array_mbi_generic, &r13);
  array_add(array_mbi_generic, &r12);
  array_add(array_mbi_generic, &r11);
  array_add(array_mbi_generic, &r10);
  array_add(array_mbi_generic, &r9);
  array_add(array_mbi_generic, &r8);
  array_add(array_mbi_generic, &r7);
  array_add(array_mbi_generic, &r6);
  array_add(array_mbi_generic, &r5);
  array_add(array_mbi_generic, &r4);
  array_add(array_mbi_generic, &r3);
  array_add(array_mbi_generic, &r2);
  array_add(array_mbi_generic, &r1);
  array_add(array_mbi_generic, &r0);
  order_array(array_mbi_generic, 0, array_size(array_mbi_generic)-1);

  Record **act_arr = (Record **) malloc(20*sizeof(Record*));
  for (int i = 0; i < 20; i++) {
    act_arr[i] = (Record*)array_get(array_mbi_generic, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 20);

  array_mbi_generic->precedes = precedes_record_double_field_decr;
  order_array(array_mbi_generic, 0, array_size(array_mbi_generic)-1);
  act_arr = (Record **) malloc(20*sizeof(Record*));
  for (int i = 0; i < 20; i++) {
    act_arr[i] = (Record*)array_get(array_mbi_generic, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr_decr, act_arr, 20);
  
  free(act_arr);
  array_free_memory(array_mbi_generic);
}



int main() {
  UNITY_BEGIN();
  RUN_TEST(test_array_mbi_is_empty_zero_el);
  RUN_TEST(test_array_mbi_is_empty_one_el);
  RUN_TEST(test_array_mbi_size_zero_el);
  RUN_TEST(test_array_mbi_size_one_el);
  RUN_TEST(test_array_mbi_size_two_el);
  RUN_TEST(test_array_mbi_add_get_one_el);
  RUN_TEST(test_array_mbi_add_get_three_el);
  RUN_TEST(test_array_mbi_generic_array_by_integer);
  RUN_TEST(test_array_mbi_generic_array_by_string);
  RUN_TEST(test_array_mbi_generic_array_by_double);
  return UNITY_END();
}
