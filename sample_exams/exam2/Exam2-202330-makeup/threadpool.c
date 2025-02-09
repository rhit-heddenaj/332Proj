#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "prettyprint.h"

#define NUM_THREADS 10

const char *stack = "abcdefghijklmnopqrstuvwxyz123456789";
int stackptr = 0;
pthread_mutex_t mutex;

char pop()
{
  if(stackptr >= strlen(stack)) {
    fprintf(stderr,
            "Buffer overflow when reading the stack. Fix your code!\n");
    return 0;
  }
  return stack[stackptr++];
}

int is_empty()
{
  return (stackptr >= strlen(stack));
}



void* worker_thread(void* arg) {
    int thread = *(int*)arg;
    
    printf("Worker thread %d started\n", thread);
    
    stackptr = thread;
    while(1) {
	pthread_mutex_lock(&mutex);
	if(is_empty()) {
	    
	    break;
	}
	char popped = pop();
	pthread_mutex_unlock(&mutex);
	printf("Thread %d processing %c\n", thread, popped);
	sleep(1);
    }
    
    return NULL;
}

int main(int argc, char **argv)
{
  /* TODO: YOUR IMPLEMENTATION GOES HERE */
  pthread_t tid[NUM_THREADS];
  int nums[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    nums[i] = i;
    pthread_create(&tid[i], NULL, worker_thread, &nums[i]);
  }
  
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  /* DO NOT REMOVE THIS LINE */
  printf("****** Everything finished ******\n");
}
