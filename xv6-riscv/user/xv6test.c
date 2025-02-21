#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

unsigned long long int target = 343;
int numThreads = 4;

void* runner(void* arg) {
        

    int thread = *(int*)arg;
    int curr = thread;
    while(curr < target) {
	printf("thread %d testing %d\n", thread+1, curr);
	if(target % curr == 0) {
	    printf("%d is a factor\n", curr);
	}
	curr+= numThreads;
    }
    exit(5);
    return NULL;

}


int main(void) {
  /* you can ignore the linter warning about this */
  //unsigned long long int target, i, start = 0;
    if (numThreads > 50 || numThreads < 1) {
	printf("Bad number of threads!\n");
    return 0;
  }

  for (int j = 0; j < numThreads; j++) {
    int* arg = (int*)malloc(sizeof(int));
    *arg = j;
    mythread_create(arg, runner);

  }


  for (int j = 0; j < numThreads; j++) {
    mythread_join();
  }

  printf("All threads complete\n"); 
  return 0;

}


