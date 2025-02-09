#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Problem 1
//
// Name: 


// Default buffer size for use with snprintf
#define BUFSIZE 128
#define NUM_CHILDREN 10

int main(int argc, char **argv) {
  int parentid = getpid();
  char idstr[BUFSIZE];
  sprintf(idstr, "%d\n", parentid);
  pid_t pids[NUM_CHILDREN];
  for (int i = 0; i < NUM_CHILDREN; i++) {
    int rc = fork();
    if (rc == 0) {
	//child
	execlp("./pretty.bin", "./pretty.bin", idstr, "Be brave and never give up!", NULL);
	perror("should not be here\n");
	exit(EXIT_FAILURE);
    } else {
	//parent
	pids[i] = rc;
    }	
  }

    for (int i = 0; i < NUM_CHILDREN; i++) {
	int status;
	waitpid(pids[i], &status, 0);
	if (WIFEXITED(status)) {
	    printf("Child %d with PID %d finished with exit code %d\n", i, pids[i], WEXITSTATUS(status)); 
	} else {
	    printf("child %d with PID %d crashed\n", i, pids[i]);
	}
    }


  printf("Parent %d finished ....\n", getpid());
  exit(0);
}

