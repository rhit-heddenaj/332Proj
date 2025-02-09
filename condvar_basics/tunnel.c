#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// constants to control number of cars and threads
#define NUM_EW_CARS 15
#define NUM_WE_CARS 15
#define NUM_AMBULANCE 7
#define TOTAL_THREADS NUM_EW_CARS + NUM_WE_CARS + NUM_AMBULANCE

// constants to define ambulance direction
#define EW_DIRECTION 1
#define WE_DIRECTION 2

// car speeds
#define EW_SPEED 3
#define WE_SPEED 2

// state variables
int ew = 0;
int we = 0;
int amb = 0;

// concurrency means
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

void *ewcar(void *arg)
{
  int tid = *(int*)arg;
  pthread_mutex_lock(&mutex);

  while (ew >= 3 || amb) {
    pthread_cond_wait(&cond, &mutex);
  }
  ew++;
  pthread_mutex_unlock(&mutex);
  printf("Car (%d) entered tunnel in EW direction...\n", tid);
  sleep(EW_SPEED);
  printf("Car (%d) exited tunnel in EW direction...\n", tid);
  pthread_mutex_lock(&mutex);
  ew--;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);
  if (amb) pthread_cond_signal(&cond3);
  return 0;
}

void *wecar(void *arg)
{
  int tid = *(int *)arg;
  pthread_mutex_lock(&mutex);
  while (we >= 1 || amb) {
    pthread_cond_wait(&cond2, &mutex);
  }
  we++;
  pthread_mutex_unlock(&mutex);
  printf("Car (%d) entered tunnel in WE direction...\n", tid);
  sleep(WE_SPEED);
  printf("Car (%d) exited tunnel in WE direction...\n", tid);
  pthread_mutex_lock(&mutex);
  we--;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond2);
  if (amb) pthread_cond_signal(&cond3);
  return 0;
}

void *ambulance(void *arg)
{
  int tid = *(int*)arg;
  int direction = EW_DIRECTION;
  printf("An ambulance has arrived\n");
  pthread_mutex_lock(&mutex);
  amb++;
  while (ew >= 3 && we >= 1) {	
    //printf("ambulance waiting\n");
    pthread_cond_wait(&cond3, &mutex);
  }
  pthread_mutex_unlock(&mutex);
  if (ew >= 3) direction = WE_DIRECTION;
  pthread_mutex_lock(&mutex);
  if(direction == EW_DIRECTION) {
    ew++;
    printf("Ambulance %d entered the tunnel in EW direction\n", tid);
  } else if (direction == WE_DIRECTION) {
    printf("Ambulance %d entered the tunnel in WE direction\n", tid);
    we++;
  }
  pthread_mutex_unlock(&mutex);

  sleep(1); // ambulance is the fastest

  pthread_mutex_lock(&mutex);
  if(direction == EW_DIRECTION) {
    printf("Ambulance %d exited the tunnel in EW direction\n", tid);
    ew--;
  } else if(direction == WE_DIRECTION) {
    printf("Ambulance %d exited the tunnel in WE direction\n", tid);
    we--;
  }
  amb--;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond3);
  if(!we && !amb) pthread_cond_signal(&cond2);
  if(ew < 3 && !amb) pthread_cond_signal(&cond);
  //pthread_mutex_unlock(&mutex);

  return 0;
}


int
main(int argc, char **argv)
{
  pthread_t threads[NUM_EW_CARS + NUM_WE_CARS + NUM_AMBULANCE];
  int tids[NUM_EW_CARS + NUM_WE_CARS + NUM_AMBULANCE];
  int i;
  srand(time(0));

  for(i = 0; i < NUM_EW_CARS; i++) {
    tids[i] = i + 1;
    pthread_create(&threads[i], 0, ewcar, &tids[i]);
  }

  for(i = NUM_EW_CARS; i < NUM_WE_CARS + NUM_EW_CARS; i++) {
    tids[i] = i + 1;
    pthread_create(&threads[i], 0, wecar, &tids[i]);
  }

  for(i = NUM_EW_CARS + NUM_WE_CARS; i < TOTAL_THREADS; i++) {
    tids[i] = i + 1;
    pthread_create(&threads[i], 0, ambulance, &tids[i]);
    // make the ambulances arrive at random times
    sleep(rand() % 10);
  }

  for(i = 0; i < TOTAL_THREADS; i++) {
    pthread_join(threads[i], 0);
  }

  printf("Everyting finished...\n");
  exit(EXIT_SUCCESS);
}
