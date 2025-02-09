#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * pipe_pid.c
 *
 * Task:
 * =====
 * In this exercise, we would like to child to send its process id back to its
 * parent. Yes we can get it from the return value of fork, but we'd like to
 * have a backup way for getting it as well.
 *
 * HINT 1:
 * =======
 * You might find the functions sprintf, snprintf, and atoi very helpful.
 *
 * HINT 2:
 * =======
 *  Alternatively, remember that everything is just a bunch of bytes.  How many
 *  bytes is an integer?
 */

int main(int argc, char **argv) {
  pid_t pid;
  int fd[2];
  int nbytes;
  char readbuff[512];

  if (pipe(fd) < 0) {
	perror("SOMETHING VERY WRONG\n");
	exit(99);
  }

  pid = fork();
  if(pid == 0) {
    // child, I am the writer
    snprintf(readbuff, 512, "%d", getpid());
    close(fd[0]);
    write(fd[1],
	  readbuff,
	  512);
    close(fd[1]);

    exit(0);
  } else {
    close(fd[1]);
    nbytes = read(fd[0],
	     readbuff,
	     512);

    if (nbytes) {
	printf("Child pid is %s\n", readbuff); 
	if (nbytes < 512) {
	    readbuff[nbytes] = 0;
	}
    }
    close(fd[0]);

  }

  // parent, I am the reader
  exit(0);
}

