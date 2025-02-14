#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

void* thread(void* arg) {
    int curr = *(int*)arg;
    for (int i = 0; i < 100; i++) {
	printf("Thread 1 says %d\n", curr);
    }
    exit(0);
    return NULL;
}

void* thread2(void* arg) {
    int blah = *(int*)arg;
    for (int i = 0; i < 100; i++) {
	printf("Thread 2 says %d\n", blah);
    }
    exit(0);
    return NULL;
}


int main(int argc, char *argv[]) {
  printf("Hello from my test case in xv6\n");
  
  
  int val1 = 9713;
  if(mythread_create(&val1, thread) < 0) {
    printf("ERROR ERROR ERROR\n");
  }
  int val2 = 6851;
  if(mythread_create(&val2, thread2) < 0) {
    printf("ERROR ERROR ERROR\n");
  }


  mythread_join(11);
  mythread_join(8);
  

  exit(0);
}







