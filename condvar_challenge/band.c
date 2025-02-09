/* Copyright 2021 Rose-Hulman */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

/**
  Imagine a group of friends are getting together to play music, but
  they are arriving at different times.  Arriving can happen at any
  time (e.g. when some other friends are playing).

  There are 3 different kinds of friends - drummers, singers, and
  guitarists.  It takes one of each kind to make a band, plus only
  1 band can be playing at once.  Once those conditions are met, the
  players can start playing and stop playing in any order.  However,
  all 3 players must stop playing before a new set of 3 can start
  playing.

  Example output:

  drummer arrived
  drummer arrived
  guitarist arrived
  guitarist arrived
  singer arrived
  drummer playing
  guitarist playing
  singer playing
  singer arrived
  singer arrived
  drummer arrived
  guitarist arrived
  drummer finished playing
  guitarist finished playing
  singer finished playing
  singer playing
  guitarist playing
  drummer playing
  singer finished playing
  guitarist finished playing
  drummer finished playing
  guitarist playing
  drummer playing
  singer playing
  guitarist finished playing
  drummer finished playing
  singer finished playing
  Everything finished.


 **/

int DRUM = 0;
int SING = 1;
int GUIT = 2;

char* names[] = {"drummer", "singer", "guitarist"};

int drumqueue = 0;
int singqueue = 0;
int guitqueue = 0;

int drumplaying = 0;
int singplaying = 0;
int guitplaying = 0;

int drums = 0;
int singers = 0;
int guitars = 0;

int play = 0;


// because the code is similar, we'll just have one kind of thread
// and we'll pass its kind as a parameter


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


pthread_cond_t drumcond = PTHREAD_COND_INITIALIZER;
pthread_cond_t singcond = PTHREAD_COND_INITIALIZER;
pthread_cond_t gcond = PTHREAD_COND_INITIALIZER;

pthread_cond_t playcond = PTHREAD_COND_INITIALIZER;


//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* friend(void * kind_ptr) {
  int kind = *((int*) kind_ptr);
  printf("%s arrived\n", names[kind]);
  
  pthread_mutex_lock(&mutex);
  if(kind==DRUM) {
    drums++;
    while(drumqueue) {
	pthread_cond_wait(&drumcond, &mutex);
    }
    drumqueue = 1;
  } else if (kind == SING) {
    singers++;
    while(singqueue) {
	pthread_cond_wait(&singcond, &mutex);
    }
    singqueue = 1;
  } else {
    guitars++;
    while(guitqueue) {
	pthread_cond_wait(&gcond, &mutex);
    }
    guitqueue = 1;
  }


  //printf("%s joined queue\n", names[kind]);

  while(!play) {
    if(drumqueue && singqueue && guitqueue && !singplaying && !guitplaying && !drumplaying) {
	play = 1;
	pthread_cond_broadcast(&playcond);
    } else {
	pthread_cond_wait(&playcond, &mutex);
    }
  }
  //pthread_cond_broadcast(&playcond);
  if(kind == DRUM) {
    drumplaying = 1;
  } else if (kind == SING) {
    singplaying = 1;
  } else {
    guitplaying = 1;
  }

  if(singplaying && guitplaying && drumplaying) {
    play = 0;
    drumqueue = 0;
    singqueue = 0;
    guitqueue = 0;
  }

  pthread_mutex_unlock(&mutex);
  printf("%s playing\n", names[kind]);
  sleep(1);
  printf("%s finished playing\n", names[kind]);

  //everything is done playing
  
  pthread_mutex_lock(&mutex);
  
  if(kind == DRUM) {
    drumplaying = 0;
    drums--;
    if(drums > 0) pthread_cond_signal(&drumcond);
  } else if (kind == SING) {
    singplaying = 0;
    singers--;
    if(singers>0)pthread_cond_signal(&singcond);
  } else {
    guitplaying = 0;
    guitars--;
    if(guitars>0)pthread_cond_signal(&gcond);
  }

  if(!drumplaying && !singplaying && !guitplaying) {
    if(drums>0 && singers > 0 && guitars > 0) pthread_cond_broadcast(&playcond);
  }


  pthread_mutex_unlock(&mutex);
  return NULL;
}

pthread_t friends[100];
int friend_count = 0;

void create_friend(int* kind) {
  pthread_create(&friends[friend_count], NULL, friend, kind);
  friend_count++;
}

int main(int argc, char **argv) {

  create_friend(&DRUM);
  create_friend(&DRUM);
  create_friend(&GUIT);
  create_friend(&GUIT);
  sleep(1);
  create_friend(&SING);
  create_friend(&SING);
  create_friend(&DRUM);
  create_friend(&GUIT);
  create_friend(&SING);

  // all threads must be created by this point
  // note if you didn't create an equal number of each, we'll be stuck forever
  for (int i = 0; i < friend_count; i++) {
    pthread_join(friends[i], NULL);
  }
  //printf("drum: %d, sing: %d, g: %d\n", drum, sing, g);
  printf("Everything finished.\n");
  

 

}
