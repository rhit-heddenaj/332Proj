#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>


void* fn1(void* arg) {
    int curr = *(int*)arg;
    for (int i = 0; i < 12; i++) {
	printf("Function 1 says %d\n", curr + i);
    }
    exit(5);
    return NULL;
}

void* fn2(void* arg) {
    int blah = *(int*)arg;
    for (int i = 0; i < 15; i++) {
	printf("Function 2 says %d\n", blah + i);
    }
    exit(5);
    return NULL;
}






int main(int argc, char *argv[]) {
  for(int i = 0; i < 30; i++) {
    if(i % 2 == 0) {
	int num = i * 30;
	if(mythread_create(&num, fn1) == -1) {
	    printf("Error creating thread with function 1\n");
	}
    } else {
	int num = i * 20 + 91;
	if(mythread_create(&num, fn2) == -1) {
	    printf("Error creating thread with function 2\n");
	}
    }
  } 

  for(int i = 0; i < 30; i++) {
    mythread_join();
  }
 
  printf("Finished waiting :)\n");

  exit(0);
}







