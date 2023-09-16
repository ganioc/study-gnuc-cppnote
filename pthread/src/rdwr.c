#include "rdwr.h"

int pthread_rdwr_init_np(pthread_rdwr_t *rdwrp, pthread_rdwrattr_t *attrp){
    rdwrp->reader_reading = 0;
    rdwrp->writer_writing = 0;
    pthread_mutex_init(&(rdwrp->mutex), NULL);
    pthread_cond_init(&(rdwrp->lock_free), NULL);
    return 0;
}

int pthread_rdwr_rlock_np(pthread_rdwr_t *rdwrp){
    pthread_mutex_lock(&(rdwrp->mutex));

    while(rdwrp->writer_writing){
        pthread_cond_wait(&(rdwrp->lock_free), &(rdwrp->mutex));
    }

    rdwrp->reader_reading++;

    pthread_mutex_unlock(&(rdwrp->mutex));

    return 0;
}
int pthread_rdwr_wlock_np(pthread_rdwr_t *rdwrp){
    pthread_mutex_lock(&(rdwrp->mutex));

    while(rdwrp->writer_writing || rdwrp->reader_reading){
        pthread_cond_wait(&(rdwrp->lock_free), &(rdwrp->mutex));
    }
    rdwrp->writer_writing++;

    pthread_mutex_unlock(&(rdwrp->mutex));

    return 0;    
}
int pthread_rdwr_runlock_np(pthread_rdwr_t *rdwrp){
    pthread_mutex_lock(&(rdwrp->mutex));

    if(rdwrp->reader_reading == 0){
        pthread_mutex_unlock(&(rdwrp->mutex));
        return -1;
    }else{
        rdwrp->reader_reading--;
        if(rdwrp->reader_reading == 0){
            pthread_cond_signal(&(rdwrp->lock_free));
            
        }
        pthread_mutex_unlock(&(rdwrp->mutex));
        return 0;
    }

    // pthread_mutex_unlock(&(rdwrp->mutex));

    // return 0;    
}
int pthread_rdwr_wunlock(pthread_rdwr_t *rdwrp){
    pthread_mutex_lock(&(rdwrp->mutex));

    if(rdwrp->writer_writing == 0){
        pthread_mutex_unlock(&(rdwrp->mutex));
        return -1;
    }else{
        rdwrp->writer_writing = 0;
        pthread_cond_broadcast(&(rdwrp->lock_free));
        pthread_mutex_unlock(&(rdwrp->mutex));
        return 0;
    }      
}

int main(void){
    printf("rdwr\r\n");
    return 0;
}


