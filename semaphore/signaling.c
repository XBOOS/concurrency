#include<stdlib.h> //general utilities
#include<sys/types.h> //primitive system data types
#include<errno.h>
#include<unistd.h> //Symbolic Constants
#include<pthread.h> //POSIX THreads
#include<semaphore.h> //semaphore
#include<stdio.h>
#include<string.h>
//My storyline:
//simulating a guy on the street to ask for a girl's telephone number
//what constraint we need to impose is that he must say hello and accomplishemnt her first 
//thus we need  a signaling mechanism to enforce the serialization

//thread handler and starting point
//I should've used prototype first and defined them after the main()

sem_t mySignal;
void * sayHi(void * ptr){
  char *call = (char *) ptr;
  printf("Ben : Hi %s, you are so gorgeous!\n",call);
  sem_post(&mySignal);
  pthread_exit(0);
}

void *askPhoneNum(void * ptr){
 
  sem_wait(&mySignal);
  printf(" Ben: May I knwo your phone number?\n");

  pthread_exit(0);
}

//global vars
//semaphores are declared global so they can be accessed in main() and in thread routine;
//here the sephore is used as a mySignal
int main(){
 pthread_t thread_a;
 pthread_t thread_b;

 sem_init(&mySignal,0,0); //initial the semaphore to 0 to act like a mySignal
 
 char* ptr;
 ptr = (char *)malloc (50*sizeof(char));
 strcpy(ptr,"blonde");
 
// pthread_create(&thread_a,NULL,(void *)&sayHi, (void *)ptr);
 
 pthread_create(&thread_b,NULL,(void *)&askPhoneNum,NULL);
 pthread_create(&thread_a,NULL,(void *)&sayHi, (void *)ptr);
 free(ptr);
 pthread_join(thread_a,NULL);
 pthread_join(thread_b,NULL);

 sem_destroy(&mySignal);


  return 0;
}
