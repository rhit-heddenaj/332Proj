#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void do_nothing(int ignored) {
  return;
}

void setsighandler(int signum, void (*handler)(int)) {
  struct sigaction act;

  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(signum, &act, NULL);
}

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
    setsighandler(SIGCONT, do_nothing);
    printf("Created child with pid = %d\n", getpid());
    pause();
    child_fn(my_pid);
    exit(EXIT_SUCCESS);
  }

  parent_fn(my_pid);
  wait(0);

  printf("Parent done and is now leaving...\n");
  exit(EXIT_SUCCESS);
}
