#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Problem 2
//
// Name: 


// Default buffer size for use with snprintf
#define BUFSIZE 128
#define NUM_CHILDREN 10


void alarm_handler(int signum) {
    exit(99);
}

int main(int argc, char **argv) {
  pid_t pids[NUM_CHILDREN];
  char idstr[BUFSIZE];
  sprintf(idstr, "%d\n", getpid());
  signal(SIGALRM, alarm_handler);
  for (int i = 0; i < NUM_CHILDREN; i++) {
    int rc = fork();
    if (rc == 0) {
	//child
	pid_t cpid = getpid();
	pids[i] = cpid;
	if (cpid % 4 == 0) {
	    printf("Child %d is bad, will not execute\n", cpid);
	} else {
	    alarm(5);
	    execlp("./prettier.bin", "./prettier.bin", idstr, "Be brave and never give up!", NULL);
	    perror("SHOULD NOT BE HERE!\n");
	    exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
    } else {
	//parent
	pids[i] = rc;
    }
  }

  for (int i = 0; i < NUM_CHILDREN; i++) {
	int status;
	waitpid(pids[i], &status, 0);
	if (WIFEXITED(status)) {
	    if (WEXITSTATUS(status) == 99) {
		printf("Child %d with PID %d timed out!\n", i, pids[i]);
	    } else {
		printf("Child %d with PID %d finished with exit code %d\n", i, pids[i], WEXITSTATUS(status));
	    }
	} else {
	    printf("Child with PID %d crashed\n", pids[i]);
	}
  }

  printf("Parent %d finished ....\n", getpid());
  exit(0);
}

