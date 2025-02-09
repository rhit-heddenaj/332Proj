#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void parent_fn(int pid) {
  printf("Hello from the parent with pid = %d\n", pid);
}

void child_fn(int pid) {
  printf("Hello from the child with pid = %d\n", pid);
  sleep(1);
}

int main(int argc, char **argv) {
  int rc, my_pid;

  my_pid = getpid();
  rc = fork();
  if(rc < 0) {
    perror("PANIC: fork failed.");
    exit(EXIT_FAILURE);
  }

  if(!rc) {
    child_fn(my_pid);
    exit(EXIT_SUCCESS);
  }

  parent_fn(my_pid);
  wait(0);

  printf("Parent done and is now leaving...\n");
  exit(EXIT_SUCCESS);
}
