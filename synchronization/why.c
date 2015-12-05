#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int cnt = 0;
void * worker (void *ptr){
    int i;
    for (i=0;i<50000;i++)
        cnt++;
}

#define NUM_THREADS 2
int main(void){
    pthread_t threads[NUM_THREADS];
    int i,res;

    for (i=0;i<NUM_THREADS;i++){
        res = pthread_create(&threads[i],NULL,worker,NULL);
    }

    for (i=0;i<NUM_THREADS;i++){
        res = pthread_join(threads[i],NULL);

    }

    //print result
    //here to see why we need to deal with synchronization
    //each time the result is different and not what we what ---10000
    //so why multiple threads deal with the same data, something's gonna be wrong
    printf("Final value: %d\n",cnt);

}

