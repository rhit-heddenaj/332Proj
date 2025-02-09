#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "critical.h"
#include "prettyprint.h"

// array of all test cases, first and last element should always be NULL
void (*test_fn[])(void) = { 0, test1, test2, test3, 0, };

// descriptions for each test case, first and last should always be Invalid
// OCD calm down, okay to go over 79 chars here!

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int bcount = 0;
int rcount = 0;


const char *descriptions[] = {
  "Invalid",
  "All red threads, should go 2 by 2.",
  "All blue threads, should go 2 by 2.",
  "All threads arrive together, they go 3 by 3 by which ones go in non-determined.",
  "Invalid",
};

// state of the world

// condition variables and mutex lock

void *red(void *arg)
{
  unsigned long tid = (unsigned long)arg;

  pr_red("Red thread %lu arrived\n", tid); 

  pthread_mutex_lock(&mutex);
  while(rcount >= 2 || bcount + rcount >= 3) {
    pthread_cond_wait(&cond, &mutex);
  }
  rcount++;
  pr_red("Red thread %lu entering critical section\n", tid);
  pthread_mutex_unlock(&mutex);
  sleep(1);
  pr_red("Red thread %lu leaving critical section\n", tid);
  pthread_mutex_lock(&mutex);
  rcount--;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
  
  return 0;
}

void *blue(void *arg)
{
  unsigned long tid = (unsigned long)arg;
  pr_red("Blue thread %lu arrived\n", tid); 

  pthread_mutex_lock(&mutex);
  while(bcount >= 2 || bcount + rcount >= 3) {
    pthread_cond_wait(&cond, &mutex);
  }
  bcount++;
  pr_red("Blue thread %lu entering critical section\n", tid);
  pthread_mutex_unlock(&mutex);
  sleep(1);
  pr_red("Blue thread %lu leaving critical section\n", tid);
  pthread_mutex_lock(&mutex);
  bcount--;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
  
  return 0;
  return 0; 
}

int main(int argc, char **argv)
{
  int test_num = -1;

  if(argc < 2) {
    fprintf(stderr, "Usage: %s <test_num>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  test_num = atoi(argv[1]);
  if(test_num >= ARRAY_SIZE(test_fn, void(*)(void)) || !test_fn[test_num]) {
    fprintf(stderr, "Invalid test number %d, out of range of available tests\n",
            test_num);
    exit(EXIT_FAILURE);
  }

  pr_green("Running test number %d: %s\n\n", test_num, descriptions[test_num]);
  test_fn[test_num]();

  exit(0);
}
