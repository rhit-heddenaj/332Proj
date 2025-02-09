#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Problem 4
//
// Name: 


// IMPORTANT: buffer size for use with ALL reads and writes
#define BUFSIZE 1000

int main(int argc, char **argv) {


  int fd[2];
  pipe(fd);
  if (fork() == 0) {
    //child
    //const char *msg = "hello world!";
    //printf("msg: %s\n", msg);
    const char *msg = argv[1];
    write(fd[1], msg, strlen(msg));
    close(fd[1]);
    exit(0); 
  } else {
    //parent
    close(fd[1]);
    char buf[BUFSIZE];
    if (read(fd[0], buf, BUFSIZE) > 0) {
	char fd0_str[BUFSIZE];
	char fd1_str[BUFSIZE];
	sprintf(fd0_str, "%d", fd[0]);
	sprintf(fd1_str, "%d", fd[1]);
	printf("this is what is passed: %s\n", fd0_str);
	execlp("./buffalosay.bin", "./buffalosay.bin", fd0_str, fd1_str, NULL);
    }
    close(fd[0]);
    exit(0);
  }

  printf("Parent %d finished ....\n", getpid());
  exit(0);
}

