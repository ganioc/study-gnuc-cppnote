#pragma once

#include <pthread.h>

typedef struct llist_node{
    int index;
    void *datap;
    struct llist_node *nextp;
    pthread_mutex_t mutex;
} llist_node_t;

typedef llist_node_t* llist_t;

int llist_init(llist_t* llistp);
int llist_insert_data(int index, void *datap, llist_t *llistp);
int llist_remove_data(int index, void **datapp, llist_t *llistp);
int llist_find_data(int index, void **datapp, llist_t *llistp);
int llist_change_data(int index, void *datap, llist_t *llistp);
int llist_show(llist_t *llistp);

