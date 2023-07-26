
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int ,int);


void testllst();
