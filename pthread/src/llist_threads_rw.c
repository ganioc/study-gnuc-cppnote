#include <stdio.h>
#include <pthread.h>

#include <stdbool.h>

#include "llist.h"

typedef struct linkedlist{
    llist_node_t *first;
    pthread_rwlock_t  rwlock;
}linkedlist_t;

int linkedlist_init(linkedlist_t *llistp){
    llistp->first = NULL;
    pthread_rwlock_init(&(llistp->rwlock), NULL);


    return 0;
}
int linkedlist_insert_data(int index, void *datap, linkedlist_t *llistp){
    llist_node_t *cur, *prev, *new;
    int found = false;
    pthread_rwlock_wrlock(&(llistp->rwlock));

    pthread_rwlock_unlock(&(llistp->rwlock));
    return 0;
}
int main(void){
    printf("llist threads rw\r\n");

    return 0;
}