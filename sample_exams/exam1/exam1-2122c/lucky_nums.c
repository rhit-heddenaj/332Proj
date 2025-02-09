#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

  
#define MAX_CHAIN 5

int main(int argc, char** argv) {

    int pid = 0;

    // not much sample code needed for this assignment, modify this as
    // you see fit
    
    while (1) {
	int rc = fork();
	if (rc == 0) {
	    //child
	    if (getpid() % 10 == 7) {
		//lucky child
		printf("Lucky child pid %d created\n", getpid());
		pid = getpid();
		exit(1);
	    } else {
		//unlucky child
		printf("Unlucky child pid %d exiting\n", getpid());
		exit(0);
	    }	
	} else {
	    //parent
	    int status;
	    waitpid(rc, &status, 0);
	    if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 1) {
		    printf("Child running forever\n");
		    while(1);
		}
	    } else {
		exit(EXIT_SUCCESS);
	    }
	}
    }

    printf("parent %d thinks it found a good process %d \n", getpid(), pid);

    printf("parent running forever\n");    
    while(1);
}
