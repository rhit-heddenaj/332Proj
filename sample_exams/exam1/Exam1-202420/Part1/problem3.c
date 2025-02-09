#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

// Default buffer size for use with snprintf
#define BUFSIZE 128
#define NUM_CHILDREN 10

void setsighandler(int signum, void (*handler)(int))
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(signum, &act, NULL);
}

void alarm_handler(int signum) {
    // Exit with status 99 when the alarm goes off (timeout)
    exit(99);  
}

int main(int argc, char **argv) {
    pid_t pids[NUM_CHILDREN];
    char idstr[BUFSIZE];
    sprintf(idstr, "%d\n", getpid());
    
    for (int i = 0; i < NUM_CHILDREN; i++) {
        int rc = fork();
        if (rc == 0) {
            // Child process
            setsighandler(SIGALRM, alarm_handler); // Set alarm handler in child

            pid_t cpid = getpid();
            pids[i] = cpid;

            if (cpid % 4 == 0) {
                // Simulate "bad" child that doesn't execute
                printf("Child %d is bad, will not execute\n", cpid);
                sleep(6);  // This sleep allows the alarm in the parent to trigger
                exit(0);   // This child exits after timeout
            } else {
                // For non-"bad" children, start the alarm
                alarm(5);  // Set alarm to trigger in 5 seconds

                execlp("./bonus.bin", "./bonus.bin", idstr, "Be brave and never give up!", NULL);

                // If execlp fails, this will execute
                perror("SHOULD NOT BE HERE!\n");
                exit(EXIT_FAILURE);  
            }
            exit(EXIT_SUCCESS);  // In case no timeout occurs
        } else {
            // Parent process
            pids[i] = rc;
        }
    }

    // Parent waits for children and checks for timeouts
    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;
        
        // Wait for the child to finish, with timeout handling
        int wait_status = waitpid(pids[i], &status, 0);
        
        if (wait_status == -1) {
            // Error occurred in waitpid
            perror("waitpid error");
            continue;
        }

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 99) {
                // This means the child timed out
                printf("Child %d with PID %d timed out!\n", i, pids[i]);
            } else {
                // Child finished normally
                printf("Child %d with PID %d finished with exit code %d\n", i, pids[i], WEXITSTATUS(status));
            }
        } else {
            // If child crashed unexpectedly
            printf("Child with PID %d crashed\n", pids[i]);
        }
    }

    printf("Parent %d finished ....\n", getpid());
    exit(0);
}
