#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond;

pthread_mutex_t mutex;

int num = 0;

void *thread(void *arg)
{
	char *letter = (char *)arg;
	//printf("letter: %c\n", *letter);
	printf("%c wants to enter the critical section\n", *letter);
	pthread_mutex_lock(&mutex);	
        while (num >= 3) {
	    //printf("%c is waiting with num %d\n", *letter, num);
	    //pthread_mutex_lock(&mutex);
	    pthread_cond_wait(&cond, &mutex);
	}
	num++;
	pthread_mutex_unlock(&mutex);
	printf("%c is in the critical section\n", *letter);
	sleep(5);
	printf("%c has left the critical section\n", *letter);
	//printf("num: %d\n", num);
	pthread_mutex_lock(&mutex);
	num--;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	return NULL;
}

int
main(int argc, char **argv)
{
	pthread_t threads[8];
	pthread_cond_init(&cond, 0);
	pthread_mutex_init(&mutex, 0);
	int i;
	char *letters = "abcdefgh";

	for(i = 0; i < 8; ++i) {
		pthread_create(&threads[i], NULL, thread, &letters[i]);

		if(i == 4)
			sleep(4);
	}

	for(i = 0; i < 8; i++) {
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	printf("Everything finished...\n");

	return 0;
}
