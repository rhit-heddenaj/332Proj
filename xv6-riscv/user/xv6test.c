#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

void* thread(void* arg) {
    
    printf("blah\n");
    return NULL;

}

void* thread2(void* arg) {
    
    printf("blah\n");
    return NULL;

}


int main(int argc, char *argv[]) {
  printf("Hello from my test case in xv6\n");
  
  //printf("thread addr: %p\n", thread);

  //spoon(thread);
  mythread_create(11, thread);

  //printf("thread2 addr: %p\n", thread2);
  mythread_create(8, thread2);

  mythread_join(11);
  mythread_join(8);
  
  //spoon(thread2);

  exit(0);
}







