#include<stdlib.h> //general utilities
#include<sys/types.h> //primitive system data types
#include<errno.h>
#include<unistd.h> //Symbolic Constants
#include<pthread.h> //POSIX THreads
#include<semaphore.h> //semaphore
#include<stdio.h>
#include<string.h>
#include<assert.h>


int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
//pthread_mutex_init(&m, NULL);
//assert(r == 0); // always check success!
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void Pthread_mutex_lock(pthread_mutex_t *mutex) {
int rc = pthread_mutex_lock(mutex);
assert(rc == 0);
}

void Pthread_mutex_unlock(pthread_mutex_t *mutex){
int rc = pthread_mutex_unlock(mutex);
assert(rc == 0);
}

int Pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex){
int rc = pthread_cond_wait(cond,mutex);
assert(rc == 0);
return rc;
}

int Pthread_cond_signal(pthread_cond_t *cond){
int rc = pthread_cond_signal(cond);
assert(rc == 0);
return rc;
}

void thr_exit() {
  Pthread_mutex_lock(&m);
  done = 1;
  Pthread_cond_signal(&c);
  Pthread_mutex_unlock(&m);

}

void *child(void *arg){
  printf("child\n");
  thr_exit();
  printf("child finished\n");
  return NULL;

}

void thr_join(){
  Pthread_mutex_lock(&m);
  while (done==0)
    Pthread_cond_wait(&c,&m);
  Pthread_mutex_unlock(&m);

}

int main(int argc, char *argv[]){
  printf("parent: begin\n");
  pthread_t p;
  int rc=pthread_create(&p,NULL,&child,NULL);
  assert(rc==0);
  thr_join();
  printf("parent: end\n");
  return 0;

}
