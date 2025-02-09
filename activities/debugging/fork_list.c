#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5

//
// The goal of the source code below is for the parent process to create
// NUM_CHILDREN child processes and then wait for them in the order they were
// created. To do so, it uses an array called `child_pids`.
// The code contains a bug, so use gdb to find the debug and fix it.
//
int main(int argc, char **argv) {
  int rc, child_pids[NUM_CHILDREN];
  int i;

  for(i = 0; i < NUM_CHILDREN; i++) {
    rc = fork();
    if(rc == 0) {
      printf("Child %d started, will sleep for %d seconds \n",
             getpid(), 5-i);
      // save the child's pid so we can wait in order
      child_pids[i] = getpid();

      // do child stuff
      sleep(5-i);

      // done, exit.
      exit(EXIT_SUCCESS);
    }
    // continue to fork next child
  }

  // wait for the children in the order in which they were created.
  for(i = 0; i < NUM_CHILDREN; i++) {
    rc = waitpid(child_pids[i], 0, 0);
    printf("Child %d returned, continuing to the next (if any)...\n",
           rc);
  }

  printf("Parent done and is now leaving...\n");
  exit(EXIT_SUCCESS);
}
