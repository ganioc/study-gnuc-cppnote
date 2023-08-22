#include <stdio.h>

#include "atm.h"

void atm_server_int(int argc, char**argv){

}

int main(int argc, char**argv){
    char req_buf[COMM_BUFF_SIZE];
    char resp_buf[COMM_BUFF_SIZE];
    int conn;
    int trans_id;
    int done = 0;

    printf("server start\n");

    atm_server_int(argc, argv);

    //loop for ever

    for(;;){

    }

    return 0;
}