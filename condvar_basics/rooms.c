#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// Constants in the code
#define FIRST_ROOM_CAPACITY 5
#define FIRST_ROOM_SERVICE_RATE 1

#define SECOND_ROOM_CAPACITY 2
#define SECOND_ROOM_SERVICE_RATE 2
#define WAITING_ROOM_CAPACITY 2

#define NUM_PEOPLE_ARRIVING 10

// capture the of customers that leave early
int num_left_customers = 0;
// TODO: Define other state of the world variables here
int first = 0;
int second = 0;
int swait = 0;

// TODO: Define your mutex locks and condition variables:

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void *customer(void *arg)
{
  long int tid = (long int)arg;
  
  printf("[Customer %ld] Just arrived at first room...\n", tid);
  pthread_mutex_lock(&mutex);
  // Enter the first room.
  while (first >= FIRST_ROOM_CAPACITY) {
    pthread_cond_wait(&cond, &mutex);
  }

  first++;
  pthread_mutex_unlock(&mutex);

  printf("[Customer %ld] Entered first room...\n", tid);
  sleep(FIRST_ROOM_SERVICE_RATE);
  printf("[Customer %ld] Left first room...\n", tid);
  pthread_mutex_lock(&mutex);
  first--;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);


  if (swait >= WAITING_ROOM_CAPACITY) {
    printf("[Customer %ld] Left unhappy because waiting room is full...\n", tid);
    num_left_customers++;
    return 0;
  }

  // You might want to check if you need to enter the waiting room here or leave
  // here...
  // if(some condition) {
  //   printf("[Customer %ld] Left unhapy because waiting room is full...\n", tid);
  //   return 0;
  // }

  // In case the customer wants to enter the waiting room, you might want to
  // print the following:

  printf("[Customer %ld] Joined the waiting room for second room...\n", tid);
  pthread_mutex_lock(&mutex);
  swait++;
  while(second >= SECOND_ROOM_CAPACITY) {
    pthread_cond_wait(&cond2, &mutex);
  }
  swait--;
  pthread_mutex_unlock(&mutex);

  // Enter the second room
  pthread_mutex_lock(&mutex);
  second++;
  pthread_mutex_unlock(&mutex);
  printf("[Customer %ld] Entered second room...\n", tid);
  sleep(SECOND_ROOM_SERVICE_RATE);
  printf("[Customer %ld] Left second room...\n", tid);
  pthread_mutex_lock(&mutex);
  second--;
  pthread_mutex_unlock(&mutex);
  // Done, time to leave...
  pthread_cond_signal(&cond2);
  return 0;
}

int
main(int argc, char **argv)
{
  int i;
  long int tids[NUM_PEOPLE_ARRIVING];
  pthread_t threads[NUM_PEOPLE_ARRIVING];
  srand(time(0));

  for(i = 0; i < NUM_PEOPLE_ARRIVING; i++) {
    tids[i] = i + 1;
    pthread_create(&threads[i], 0, customer, (void*)tids[i]);
    if(!(i % 2))
      sleep(rand() % 2);
  }

  for(i = 0; i < NUM_PEOPLE_ARRIVING; i++) {
    pthread_join(threads[i], 0);
  }

  printf("Everything finished: %d customers left unhappy...\n",
         num_left_customers);
  exit(EXIT_SUCCESS);
}
