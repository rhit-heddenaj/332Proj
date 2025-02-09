#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Exercise 3
 *
 * In this exercise, we would like to create a cascade of children, each one
 * creating a child of its own.
 *
 * Starting from a parent, we would like to see something like this:
 * parent -> child 1 -> child 2 -> child 3 -> child 4
 *
 * Each process will print its process id and its order in the chain.
 * So parent prints: Parent has pid: <parent pid>
 * First child prints: Child 1 has pid: <pid>
 * Second child prints: Child 2 has pid: <pid>
    *
 * Each parent must wait for its child to exit before they can exit.
 *  This means that the main parent will not exit until ALL children have
 *  exited.
 *
 * OPTIONAL: read the number of children to create from the command line.
 */

// TODO: Add your code here!


int main(int argc, char **argv) {
    int numchildren = 5;
    if (argc == 2) {
	numchildren = atoi(argv[1]);
    }

    printf("Parent has pid: %d\n", getpid());
    
    for (int i = 0; i < numchildren; i++) {
	int status;
	int rc = fork();
	if (rc != 0) {
	    //parent
	    waitpid(rc, &status, 0);
	} else {
	    //child
	    printf("Child %d has pid: %d\n", i+1, getpid());
	    exit(0);
	}
    }
    return 0;
    

/*
    } else {
	//child
	for (int i = 0; i < numchild; i++) {
	    int childrc = fork();
	    if (childrc != 0) {
		//parent
		waitpid(childrc, &status, 0);
	    } else {
		//child
		printf("child %d has pid: %d\n", i+1, getpid());
		exit(0);
	    }
	}
	exit(EXIT_SUCCESS);

    }
*/
}
