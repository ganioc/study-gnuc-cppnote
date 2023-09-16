
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "llist.h"

/* Right now, this routine simply ensures that we dont' initialize
 a list that has data on it.
*/

int llist_init(llist_t* llistp){
    if(*llistp == NULL){
        return 0;
    }else{
        return -1;
    }

}
int llist_insert_data(int index, void *datap, llist_t *llistp){
    llist_node_t *cur, *prev, *new;
    int found = false;

    for(cur = prev = *llistp; cur != NULL; prev=cur, cur=cur->nextp){
        if(cur->index == index){
            free(cur->datap);
            cur->datap = datap;
            found = true;
            break;
        }else if(cur->index > index){
            break;
        }
    }

    if(!found){
        new = (llist_node_t *)malloc(sizeof(llist_node_t));
        new->index = index;
        new->datap = datap;
        new->nextp = cur;
        if(cur == llistp){
            *llistp = new;
        }else{
            prev->nextp = new;
        }
    }
    return  0;
}


void main(){
    printf("llist app\r\n");
}