#include <stdio.h>
#include <stdlib.h>

/**
 * get_first_byte_ptr()
 *
 * This function accepts as input an unsigned integer x.
 *
 * The goal of this function is to extract the first byte in the hex
 * representation of the x. YOU MUST use pointer arithmetic to be able to
 * extract the byte, you are not allowed to use any bitwise and bit shift
 * operations.
 *
 * For example, let's say that x = 0xdeadbeef.
 * Then, this function should return 0xde.
 *  The byte we are seeking is the first from the human readable
 *  representation.
 *
 * Here's another example.
 *  get_first_byte_ptr(0x12000000) returns 0x12
 *  get_first_byte_ptr(3) return 0x00 since 3 is 0x00000003
 *
 * @param x   The unsigned integer to find the first byte for.
 * @return the first byte of x as an unsigned integer.
 */
unsigned char get_first_byte_ptr(unsigned int x) {
  // your code goes here...
  return 0;
}

/**
 * OPTIONAL:
 * get_first_byte_mask()
 *
 * Same operation as above, but use bit shifts and bit masks to find the first
 * byte.
 */
unsigned char get_first_byte_mask(unsigned int x) {
  // your code goes here...
  return 0;
}

int main(int argc, char **argv) {
  unsigned int x = 0xABFFED3A;

  printf("Test case for x = 0x%x\n", x);
  printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_ptr(x), 0xab);
  /* printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_mask(x), 0xab); */
  puts("==================================================================");

  x = 0xdeadbeef;
  printf("Test case for x = 0x%x\n", x);
  printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_ptr(x), 0xde);
  /* printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_mask(x), 0xde); */
  puts("==================================================================");

  x = 3;
  printf("Test case for x = 0x%x\n", x);
  printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_ptr(x), 0x0);
  /* printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_mask(x), 0x0); */
  puts("==================================================================");

  x = -1;
  printf("Test case for x = 0x%x\n", x);
  printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_ptr(x), 0xff);
  /* printf("Got: 0x%x, EXPECTED: 0x%x\n", get_first_byte_mask(x), 0xff); */
  puts("==================================================================");

  return 0;
}
