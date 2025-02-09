#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

#define simple_assert(message, test)                                           \
  do {                                                                         \
    if(!(test))                                                                \
      return message;                                                          \
  } while(0)
#define TEST_PASSED NULL
#define DATA_SIZE 100
#define INITIAL_VALUE 77
#define MAX_TESTS 10

/* test_funcs is an array of function pointers that store all of the test we
 * would like to run. */
char *(*test_funcs[MAX_TESTS])();

/* total number of tests registered */
static int num_tests = 0;

/* shared data that all the tests will use. */
static int data[DATA_SIZE][DATA_SIZE];

/**
 * Add a test to our list of test functions that we would like to run.
 *
 * @param test_func A pointer to the function that we would like to run.
 */
void add_test(char *(*test_func)()) {
  if(num_tests == MAX_TESTS) {
    printf("exceeded max possible tests");
    exit(1);
  }
  test_funcs[num_tests] = test_func;
  num_tests++;
}

/**
 * This setup function should run before each test
 */
void setup(void) {
  printf("starting setup\n");
  fflush(stdout);
  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      data[i][j] = INITIAL_VALUE;
    }
  }

  /* imagine this function does a lot of other complicated setup that takes a
   * long time. */
  usleep(3000000);
}

void alarm_handler(int signum) {
    printf("Test Timeout\n");
    exit(2);
}

/**
 * Run all the test in the test suite.
 */
void run_all_tests() {
    setup();
    pid_t pids[MAX_TESTS];
    signal(SIGALRM, alarm_handler);
    char buf[512];
    int fds[MAX_TESTS][2];
    for (int i = 0; i < num_tests; i++) {
	if(pipe(fds[i])<0) {
	    perror("Pipe failed\n");
	    exit(99);
	};
	pid_t rc = fork();
	if(rc == 0) {
	    alarm(3);
	    char* test_output = test_funcs[i]();
	    //printf("Test Done\n");
	    if (test_output == TEST_PASSED) {
		close(fds[i][0]);
		exit(0);
	    } else {
		//printf("test output: %s\n", test_output);
		write(fds[i][1], test_output, strlen(test_output));
		close(fds[i][1]);
		exit(1);
	    }
	} else {
	    pids[i] = rc;
	    close(fds[i][1]);
	}
    }
    
    for (int i = 0; i < num_tests; i++) {
	int status;
	pid_t pid = pids[i];
	waitpid(pid, &status, 0);
	//printf("Second loop pid for %d: %d\n", i+1, pid);
	if (WIFEXITED(status)) {
	    if(WEXITSTATUS(status) == 0) {
		printf("Test Passed\n");
	    } else if (WEXITSTATUS(status) == 1){
		int nbytes = read(fds[i][0], buf, 512);
		buf[nbytes] = 0;
		close(fds[i][0]);
		printf("Test Failed: %s\n", buf);
	    }
	} else {
	    printf("Test Crashed\n");
	}
    }
}

char *test1() {
  printf("starting test 1\n");
  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      simple_assert("test 1 data not initialized properly",
                    data[i][j] == INITIAL_VALUE);
    }
  }

  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      data[i][j] = 1;
    }
  }

  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      simple_assert("test 1 data not set properly", data[i][j] == 1);
    }
  }
  printf("ending test 1\n");
  return TEST_PASSED;
}

char *test2() {
  printf("starting test 2\n");
  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      simple_assert("test 2 data not initialized properly",
                    data[i][j] == INITIAL_VALUE);
    }
  }

  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      data[i][j] = 2;
    }
  }

  for(int i = 0; i < DATA_SIZE; i++) {
    for(int j = 0; j < DATA_SIZE; j++) {
      simple_assert("test 2 data not set properly", data[i][j] == 2);
    }
  }

  printf("ending test 2\n");
  return TEST_PASSED;
}

char *test3() {
  printf("starting test 3\n");

  simple_assert("test 3 always fails", 1 == 2);

  printf("ending test 3\n");
  return TEST_PASSED;
}

char *test4() {
  printf("starting test 4\n");
  fflush(stdout);

  int *val = NULL;
  printf("data at val is %d", *val);

  printf("ending test 4\n");
  return TEST_PASSED;
}

char *test5() {
  printf("starting test 5\n");
  fflush(stdout);

  
  while(1)
    ;

  printf("ending test 5\n");
  return TEST_PASSED;
}

int main(int argc, char **argv) {
  add_test(test1);
  add_test(test2);
  add_test(test3);
  add_test(test4); 
  add_test(test5); 
  run_all_tests();
}
