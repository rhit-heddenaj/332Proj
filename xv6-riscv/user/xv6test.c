#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int variable = 0;

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* fn1(void* arg) {
    int curr = *(int*)arg;
   
    printf("fn1 arg: %d\n", curr);
    variable += curr;
    printf("this is the new variable after fn1: %d\n", variable);
    /*
    for (int i = 0; i < 15; i++) {
	printf("Function 1 says %d\n", curr + i);
    }
    */
    exit(5);
    return NULL;
}

void* fn2(void* arg) {
    int blah = *(int*)arg;
    printf("fn2 arg: %d\n", blah);
    variable += blah;
    printf("this is the new variable after fn2: %d\n", variable);
   
    /*
    for (int i = 0; i < 15; i++) {
	printf("Function 2 says %d\n", blah + i);
    }
    */
    
    exit(5);
    return NULL;
}






int main(int argc, char *argv[]) {
  for(int i = 0; i < 30; i++) {
    if(i % 2 == 0) {
	int num = i * 30;
	int *arg = (int*)malloc(sizeof(int));
	*arg = num;
	if(mythread_create(arg, fn1) == -1) {
	    printf("Error creating thread with function 1\n");
	}
    } else {
	int num = i * 21;
	int *arg = (int*)malloc(sizeof(int));
	*arg = num;
	if(mythread_create(arg, fn2) == -1) {
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

