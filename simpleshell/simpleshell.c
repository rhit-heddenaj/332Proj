/* Copyright 2016 Rose-Hulman
   But based on idea from http://cnds.eecs.jacobs-university.de/courses/caoslab-2007/
   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_sigchld(int ignored) {
    int status;
    // https://pubs.opengroup.org/onlinepubs/9699919799/functions/waitpid.html
    while (waitpid(ignored, &status, WNOHANG) > 0) { //https://stackoverflow.com/questions/33508997/waitpid-wnohang-wuntraced-how-do-i-use-these
	printf("handling child %d\n", ignored);
    }
    exit(0);
}

void setsighandler(int signum, void (*handler)(int)) {
    struct sigaction act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(signum, &act, NULL);
}


int main() {
  char command[82];
  char *parsed_command[2];
  // takes at most two input arguments
  // infinite loop but ^C quits

  //setsighandler(SIGCHLD, handle_sigchld);

  while (1) {
    printf("SHELL%% ");
    fgets(command, 82, stdin);
    command[strlen(command) - 1] = '\0';//remove the \n
    
    int len_1;

    for(len_1 = 0;command[len_1] != '\0';len_1++){
      if(command[len_1] == ' ') {
	break;
      }
    } 



    parsed_command[0] = command;
    if(len_1 == strlen(command)){
      printf("Command is '%s' with no arguments\n", parsed_command[0]);
      parsed_command[1] = NULL;

      //Fork here and execute file
      int status;
      int rc = fork();
      if (rc < 0) {
	perror("Failed to fork a process\n");
	exit(EXIT_FAILURE);
      }

      if (rc==0) {
	//run other file (child process)
	//printf("first character: %d\n", parsed_command[0][0]);
	if (parsed_command[0][0]>48 && parsed_command[0][0] < 58) {
	    char* new_command = parsed_command[0]+1;
	    int repetitions = parsed_command[0][0] - 48;
	    printf("Actual command: %s\n", new_command);
	    for (int i = 0; i < repetitions; i++) {
		int new_rc = fork();
		if (new_rc == 0) {
		    execl(new_command, new_command,  NULL);
		    perror("AHHHH");
		    exit(EXIT_SUCCESS);
		} else {
		    wait(&status);
		}
	    }
	} else if (parsed_command[0][0]=='B' && parsed_command[0][1]=='G') {
	    char* new_command = parsed_command[0] + 2;
	    //printf("now running in background: %s\n", new_command);
	    int printfork = fork();
	    if (printfork == 0) {
		//child
		execl(new_command, new_command, NULL);
		perror("bazinga\n");
		exit(EXIT_SUCCESS);
	    } else {
		int status;
		waitpid(printfork, &status, 0);
		printf("Background command %d finished running in background\n", printfork);
	    

	    }
	} else {
	    //printf("thing: %s\n", parsed_command[0]);
	    execl(parsed_command[0], parsed_command[0], NULL);
	    perror("BIG AHHH");
	    exit(EXIT_SUCCESS);
	}

      } else {
	//continue running simpleshell (parent process)
	if (parsed_command[0][0] != 'B' || parsed_command[0][1] != 'G') {
		waitpid(rc, &status, 0);
	    if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 0) {
		    printf("executed successfully, continuing to run simpleshell\n");
		} else {
		    printf("child failed\n");
		}
	    } else {
		printf("the child exploded\n");
	    }
	}
      }

      // leave this here, do not change it
      if(!strcmp(parsed_command[0], "quit") ||
          !strcmp(parsed_command[0], "exit")) {
        exit(EXIT_SUCCESS);
      }
    } else {
      command[len_1] = '\0';
      parsed_command[1] = command + len_1 + 1;
      printf("Command is '%s' with argument '%s'\n", parsed_command[0], parsed_command[1]);
      //Fork here and execute file
      int status;
      int rc = fork();
      if (rc < 0) {
	perror("Failed to fork a process\n");
	exit(EXIT_FAILURE);
      }

      if (rc==0) {
	//run other file (child process)
	if (parsed_command[0][0]>48 && parsed_command[0][0] < 58) {
	    char* new_command = parsed_command[0]+1;
	    int repetitions = parsed_command[0][0] - 48;
	    printf("Actual command: %s\n", new_command);
	    for (int i = 0; i < repetitions; i++) {
		int new_rc = fork();
		if (new_rc == 0) {
		    execl(new_command, new_command, parsed_command[1], NULL);
		    perror("BIG KABLOOEY");
		    exit(EXIT_SUCCESS);
		} else {
		    wait(&status);
		}
	    }
	} else if (parsed_command[0][0]=='B' && parsed_command[0][1]=='G') {
	    char* new_command = parsed_command[0] + 2;
	    //printf("now running in background: %s\n", new_command);
	    int printfork = fork();
	    if (printfork == 0) {
		execl(new_command, new_command, parsed_command[1], NULL);
		perror("bazinga\n");
		exit(EXIT_SUCCESS);
	    } else {
		int status;
		waitpid(printfork, &status, 0);
		printf("background command %d finished running\n", printfork);
	    }
	} else {
	    execl(parsed_command[0], parsed_command[0], parsed_command[1],  NULL);
	    perror("BIGGER KABLOOEYE");
	    exit(EXIT_SUCCESS);
	}
      } else {
	//continue running simpleshell (parent process)
	if (parsed_command[0][0] != 'B' || parsed_command[0][1] != 'G') {
		wait(&status);
	    if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 0) {
		    printf("executed successfully, continuing to run simpleshell\n");
		} else {
		    printf("child failed\n");
		}
	    } else {
		printf("error running child\n");
	    }
	}
	}

      // leave this here, do not change it
      if(!strcmp(parsed_command[0], "quit") ||
          !strcmp(parsed_command[0], "exit")) {
        exit(EXIT_SUCCESS);
      }
    }

  }
}
