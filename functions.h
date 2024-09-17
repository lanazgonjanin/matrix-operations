#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// ###########################################################
typedef struct {
    double *csr_data;   // Array of non-zero values
    int *col_ind;       // Array of column indices
    int *row_ptr;       // Array of row pointers
    int num_non_zeros;  // Number of non-zero elements
    int num_rows;       // Number of rows in matrix
    int num_cols;       // Number of columns in matrix
} CSRMatrix;


void ReadMMtoCSR(const char *filename, CSRMatrix *matrix);
/* <Declaring the needed functions>
<Implementation occurs in functions.c>
*/

int addition(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C);
int subtraction(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C);
int multiplication(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C);
int transpose(CSRMatrix *A, CSRMatrix *C);

void deallocateMatrix(CSRMatrix *matrix);

void printMatrix(CSRMatrix *matrix);

#endif
