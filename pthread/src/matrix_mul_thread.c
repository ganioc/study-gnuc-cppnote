#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE    10

typedef int matrix_t[ARRAY_SIZE][ARRAY_SIZE];
matrix_t MA, MB, MC;


typedef struct {
    int id;
    int size;
    int row;
    int column;
    matrix_t *MA;
    matrix_t *MB;
    matrix_t *MC;
}matrix_work_order_t;

void peer_mult( matrix_work_order_t *work_orderp)
{
    int position;
    int row = work_orderp->row;
    int column = work_orderp->column;

    (*work_orderp->MC)[row][column] = 0;

    for(position = 0; position < work_orderp->size; position++){
        (*work_orderp->MC)[row][column] = (*work_orderp->MC)[row][column] \
            + ((*work_orderp->MA)[row][position] * (*work_orderp->MB)[position][column]);
    }

    free(work_orderp);

}

int main(){
    printf("matrix mult with threads\r\n");

    int size = ARRAY_SIZE, row, column, id;
    matrix_work_order_t *work_orderp;
    pthread_t peer[size*size];

    // init matrix data
    for(int i = 0; i< size; i++){
        for(int j =0; j< size; j++){
            MA[i][j] = j;
        }
    }
    for(int i = 0; i< size; i++){
        for(int j =0; j< size; j++){
            MB[i][j] = i;
        }
    } 

    // process Matrix, by row, column
    for(row = 0; row < size; row++){
        for(column = 0; column < size; column++){
            id = column + row*size;

            work_orderp = (matrix_work_order_t*)malloc(sizeof(matrix_work_order_t));

            work_orderp->id = id;
            work_orderp->size = size;
            work_orderp->row = row;
            work_orderp->column = column;
            work_orderp->MA = &MA;
            work_orderp->MB = &MB;
            work_orderp->MC = &MC;

            pthread_create(&(peer[id]), NULL, (void*)peer_mult,
                (void*)work_orderp);

        }
    }

    for(int i = 0; i< (size*size); i++){
        pthread_join(peer[i], NULL);
    }

    printf("Matrix: The rsulting matrix C is:\n");
    for(row = 0; row < size; row++){
        for(column = 0; column < size; column++){
            printf("%5d ", MC[row][column]);
        }
        printf("\n");
    }

    return 0;
}