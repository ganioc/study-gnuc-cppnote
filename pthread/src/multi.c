#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "multi.h"

int r1 = 0, r2 = 0, r3 = 0;

pthread_mutex_t r3_mutex = PTHREAD_MUTEX_INITIALIZER;

static void do_one_thing(int *d){
    printf("do_one_thing =>\n");
    int i,j,x;

    pthread_mutex_lock(&r3_mutex);

    if(r3 > 0){
        x = r3;
        r3--;
    }else{
        x = 1;
    }

    pthread_mutex_unlock(&r3_mutex);

    for(i = 0; i < 4; i++){
        printf("doing one thing\n");
        for(j = 0; j < 10000; j++){
            x = x + i;
        }
        (*d)++;
    }
}
static void do_another_thing(int *d){
    printf("do_another_thing =>\n");
    *d = 202;
    printf("another: %d\n", *d);
}

static void do_wrap_up(int d1, int d2){
    printf("do_wrap up =>\n");
    printf("%d\n", d1+d2);
}

void testPthread(void){
    printf("test multi pthreads\n");
    r3 = atoi("12");

    pthread_t thread1, thread2;
    pthread_create(
        &thread1,
        NULL,
        (void*)do_one_thing,
        (void*)&r1
    );
    pthread_create(
        &thread2,
        NULL,
        (void*) do_another_thing,
        (void*)&r2
    );
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    do_wrap_up(r1, r2);


}