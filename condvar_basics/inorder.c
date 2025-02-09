#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond;

pthread_mutex_t mutex;

int curr = 1;



void *thread(void *arg)
{
  int *num = (int *)arg;
  pthread_mutex_lock(&mutex);

  while (curr != *num) {
    //printf("curr: %d, num: %d\n", curr, *num);
    pthread_cond_wait(&cond, &mutex);
  }
  printf("%d wants to enter the critical section\n", *num);
  //sleep(1);
  printf("%d is finished with the critical section\n", *num);
  curr++;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int
main(int argc, char **argv)
{
  pthread_t threads[4];
  pthread_mutex_init(&mutex, 0);
  pthread_cond_init(&cond, 0);
  int i;
  int nums[] = {2, 1, 4, 3};

  for(i = 0; i < 4; ++i) {
    pthread_create(&threads[i], NULL, thread, &nums[i]);

    if(i == 2)
      sleep(3);
  }

  for(i = 0; i < 4; ++i) {
    pthread_join(threads[i], NULL);
  }
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  printf("Everything finished\n");

  return 0;
}
