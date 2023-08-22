#pragma once

#define COMM_BUFF_SIZE  64*1024


typedef struct workorder{
    int conn;
    char req_buf[COMM_BUFF_SIZE];
    
} workorder_t;