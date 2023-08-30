#include <stdio.h>

#define ARRAY_SIZE    10

typedef int matrix_t[ARRAY_SIZE][ARRAY_SIZE];
matrix_t MA, MB, MC;

void mult( int size,
    int row,
    int column,
    matrix_t MA,
    matrix_t MB,
    matrix_t MC)
{
    int position;

    MC[row][column] = 0;

    for(position = 0; position < size; position++){
        MC[row][column] = MC[row][column] + (MA[row][position] * MB[position][column]);
    }

}


int main(){
    printf("multiply matrix\r\n");
    int size = ARRAY_SIZE, row, column;

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

    for(row = 0; row < size; row++){
        for(column = 0; column < size; column++){
            mult(size, row, column, MA, MB, MC);
        }
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

