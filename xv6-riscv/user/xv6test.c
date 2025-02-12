#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

void* thread(void* arg) {
    //sleep(1);
    int curr = *(int*)arg;
    printf("\n %d \n", curr);
    exit(0);
    return NULL;

}

void* thread2(void* arg) {
    //sleep(2);
    int blah = *(int*)arg;
    printf("\n %d \n", blah);
    exit(0);
    return NULL;

}


int main(int argc, char *argv[]) {
  printf("Hello from my test case in xv6\n");
  
  //printf("thread1 addr: %p\n", thread);

  //spoon(thread);
  int val1 = 9713;
  mythread_create(&val1, thread);
  int val2 = 6851;
  //printf("thread2 addr: %p\n", thread2);
  mythread_create(&val2, thread2);

  //printf("Made it here lol\n");

  mythread_join(11);
  mythread_join(8);
  
  //spoon(thread2);

  exit(0);
}







