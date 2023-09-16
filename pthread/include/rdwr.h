#pragma once

#include <pthread.h>

typedef struct rdwr_var {
    int reader_reading;
    int writer_writing;
    pthread_mutex_t mutex;
    pthread_cond_t lock_free;
} pthread_rdwr_t;

typedef void* pthread_rdwrattr_t;

#define pthread_rdwrattr_default NULL;

int pthread_rdwr_init_np(pthread_rdwr_t *rdwr, pthread_rdwrattr_t *attrp);
int pthread_rdwr_rlock_np(pthread_rdwr_t *rdwrp);
int pthread_rdwr_wlock_np(pthread_rdwr_t *rdwrp);
int pthread_rdwr_runlock(pthread_rdwr_t *rdwrp);
int pthread_rdwr_wunlock(pthread_rdwr_t *rdwrp);



