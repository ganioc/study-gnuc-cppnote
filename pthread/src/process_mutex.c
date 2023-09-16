#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>

#ifndef _POSIX_THREAD_PROCESS_SHARED
#error "This platform does not support process shared mutex" 
#endif

#include "process_mutex.h"

int shared_mem_id;
int *shared_mem_ptr;
pthread_mutex_t *mptr;
pthread_mutexattr_t mutex_shared_attr;



int main(void){
    printf("process_mutex\r\n");
    pid_t child_pid;
    int status;

    /* initialize shared memory segment */
    shared_mem_id = shmget(IPC_PRIVATE, 1*sizeof(pthread_mutex_t), 0660);
    shared_mem_ptr = (int *)shmat(shared_mem_id, (void*)0, 0);
    mptr = shared_mem_ptr;

    pthread_mutexattr_init(&mutex_shared_attr);
    pthread_mutexattr_setpshared(&mutex_shared_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mptr, &mutex_shared_attr);

    if((child_pid = fork()) == 0){
        // child
        pthread_mutex_lock(mptr);

        printf("I'm in child\r\n");

        pthread_mutex_unlock(mptr);
    }else{
        // parent
        pthread_mutex_lock(mptr);

        printf("I'm in parent\r\n");

        pthread_mutex_unlock(mptr);
    }

    return 0;
}

