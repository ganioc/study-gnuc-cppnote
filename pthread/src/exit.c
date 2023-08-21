#include <string.h>

#include "exit.h"

pthread_t  thread;
static int arg;
static const int internal_error = -12;
static const int normal_error   = -10;
static const int success        = 1;

void *routine_x(void *arg_in){
    int *arg = (int *)arg_in;

    if(*arg > 10){
        pthread_exit((void*) &internal_error);
    }else if(*arg > 5){
        return((void *)&normal_error);
    }else{
        return ((void*) &success);
    }
}


int main(int argc, char **argv){
    printf("exit status of thread\n");

    pthread_t thread;
    void *statusp;

    pthread_create(&thread, NULL, routine_x, &arg);
    pthread_join(thread, &statusp);
    if(statusp == PTHREAD_CANCELED){
        printf("Thread was canceled.\n");
    }else{
        printf("Thread completed and exit status is %d\n", *(int *)statusp);

    }

    fprintf(stderr, "Error: pthread, %s\n", 
        strerror(-1));

    return 0;
}