#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

// global variable, start invalid
int *p = (int*)0xdeadbeef;

void *thread_t1(void *arg)
{
  // allocate a new page using sbrk
  p = (int*)sbrk(4096);

  // p is the start of this new page
  p[0] = 3;
  p[1] = 2;

  exit(7);
  return NULL;
}

void *thread_t2(void *arg)
{
  // sleep a bit while t1 allocates p
  sleep(10);
  printf("aijajduda\n");
  // check that the address in p have changed
  if(p == (int*)0xdeadbeef) {
    // FAIL
    printf("FAILED\n");
  }

  if(p[0] == 3 && p[2] == 2) {
    // SUCCESS
    printf("YIPPEE\n");
  } else {
    // FAIL
    printf("AHHHH\n");
  }
  printf("howdy\n");

  exit(7);
  return NULL;
}

// create threads and join them....


int main(int argc, char *argv[]) {
    printf("ajhh\n");
    mythread_create(0, thread_t1);
    printf("ajhh2\n");
    mythread_create(0, thread_t2);
    mythread_join();
    mythread_join();

  exit(0);
}
