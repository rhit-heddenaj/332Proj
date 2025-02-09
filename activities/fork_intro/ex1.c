#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// STEP 1:
// After our in-class discussion, write code here that will create two
// processes, a parent process and a child process. Each process should print
// out the following:
//    Hello from <parent|child> process with pid = <pid>.
//
// Make sure to add error checking code to account for failures to create the
// processes.

// STEP 2:
// In the child process, add the following line before the child prints its
// hello message:
//    sleep(1);
//
// Now compile and run the program, what do you see?

// STEP 3:
// Fix the problem in step 2 by adding the appropriate function call in the
// parent process.

int
main(int argc, char **argv)
{
    printf("hello\n");
    int result = fork();
    if(result != 0) {
	printf("hello from parent\n");
	wait(0);
    } else {
	sleep(1);
	printf("hello from child\n");
    }
    exit(EXIT_SUCCESS);
}

