#include<stdlib.h> //general utilities
#include<sys/types.h> //primitive system data types
#include<errno.h>
#include<unistd.h> //Symbolic Constants
#include<pthread.h> //POSIX THreads
#include<semaphore.h> //semaphore
#include<stdio.h>
#include<string.h>
//My storyline: scene 2
//After ben got to know the girl's phone number, lets say her name is Alla
//he successully invited her out! Thus they will have a date!
//Imagine that both Ben and Alla are very flexible person and dont want to set up a specific time to meet,they will try their luck. 
//However, they made a deal that if one person arrived the first, the other one must wait until the other one.
//
//Here is so called rendezvous. 
//thread handler and starting point
//I should've used prototype first and defined them after the main()



//global vars
//semaphores are declared global so they can be accessed in main() and in thread routine;
//here the sephore is used as a mySignal

sem_t benArrived;
sem_t allaArrived;
void * ben(void * ptr){
  printf("Ben : Hi , I arrived already\n");
  sem_post(&benArrived);
  sem_wait(&allaArrived);
  printf("Ben :I thoght you wouldn't come. Nice to see you\n");
  pthread_exit(0);
}

void *alla(void * ptr){
 
  printf("Alla: I arrived already\n");
  sem_post(&allaArrived);
  sem_wait(&benArrived);
  printf("Alla: Hi Ben, nice to see you.\n");
  pthread_exit(0);
}

int main(){
 pthread_t thread_a;
 pthread_t thread_b;

 sem_init(&benArrived,0,0); //initial the semaphore to 0 to act like a Signal
 sem_init(&allaArrived,0,0);
// pthread_create(&thread_a,NULL,(void *)&sayHi, (void *)ptr);
 
 pthread_create(&thread_b,NULL,(void *)&alla,NULL);
 pthread_create(&thread_a,NULL,(void *)&ben, NULL);
 pthread_join(thread_a,NULL);
 pthread_join(thread_b,NULL);

 sem_destroy(&benArrived);
 sem_destroy(&allaArrived);


  return 0;
}
