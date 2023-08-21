#include <stdio.h>

#include "llst.h"


int shared_mem_id;
int *shared_mem_ptr;
int *r1p;
int *r2p;

void do_one_thing(int *d){
    printf("do_one_thing =>\n");
    *d = 111;
    printf("one: %d\n", *d);
}
void do_another_thing(int *d){
    printf("do_another_thing =>\n");
    *d = 222;
    printf("another: %d\n", *d);
}

void do_wrap_up(int d1, int d2){
    printf("do_wrap up =>\n");
    printf("%d\n", d1+d2);
}

void testllst(){
    pid_t child1_pid, child2_pid;
    int status;


    printf("testllst() =>\n");

    /* initialize shared memory segment */
    shared_mem_id = shmget(IPC_PRIVATE, 2*sizeof(int), 0660);
    shared_mem_ptr = (int *)shmat(shared_mem_id, (void *)0, 0);

    r1p =  shared_mem_ptr;
    r2p = (shared_mem_ptr + 1);
    *r1p = 0;
    *r2p = 0;

    if((child1_pid = fork()) == 0){
        do_one_thing(r1p);
        exit(0);
    }
    if((child2_pid = fork()) == 0){
        do_another_thing(r2p);
        exit(0);
    }

    waitpid(child1_pid, &status, 0);
    waitpid(child2_pid, &status, 0);

    do_wrap_up(*r1p, *r2p);

}
  