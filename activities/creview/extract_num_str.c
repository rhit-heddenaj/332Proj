#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * extract_num_str()
 *
 * Given a string as the input, this function will extract a substring that
 * includes the continuous positive numbers part in the string. The continuous
 * number part must not include any other characters but numbers.
 *
 * You should allocated a new string on the heap to hold the found substring.
 *
 * You can assume there should be ONE and ONLY ONE continuous positive number
 * part in the input string.
 *
 * NOTE: you don't need to free the newly created space in the function.
 *
 * For example:
 *   extract_num_str("ABC123XYZ") -> "123"
 *   extract_num_str("332 rocks") -> "332"
 *   extract_num_str("hello 812877") -> "812877"
 *   extract_num_str("Just 1 number here") -> "1"
 *
 * HINT:
 *  You may want to do this in two steps:
 *    1. Calculate how long the substring is going to be, then allocated a new
 *       string to hold that amount (don't forget your null terminators).
 *
 *    2. Copy the numerical substring into the newly allocated string.
 *
 */
char *extract_num_str(char *str) {
  // Your code goes here.
}

int main(int argc, char **argv) {
  char *s_out;
  // test[0] is input, test[1] is expected output!
  char *test1[2] = {"ABC123XYZ", "123"};
  char *test2[2] = {"332 rocks", "332"};
  char *test3[2] = {"hello 812877", "812877"};
  char *test4[2] = {"Just 1 number here", "1"};

  puts("########### Running test 1 ##############");
  s_out = extract_num_str(test1[0]);
  printf("Got: %s, Expected: %s\n", s_out, test1[1]);
  free(s_out);
  puts("");

  puts("########### Running test 2 ##############");
  s_out = extract_num_str(test2[0]);
  printf("Got: %s, Expected: %s\n", s_out, test2[1]);
  free(s_out);
  puts("");

  puts("########### Running test 3 ##############");
  s_out = extract_num_str(test3[0]);
  printf("Got: %s, Expected: %s\n", s_out, test3[1]);
  free(s_out);
  puts("");

  puts("########### Running test 4 ##############");
  s_out = extract_num_str(test4[0]);
  printf("Got: %s, Expected: %s\n", s_out, test4[1]);
  free(s_out);

  return 0;
}

