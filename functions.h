#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    double *csr_data;
    int *col_ind;
    int *row_ptr;
    int num_non_zeros;
    int num_rows;
    int num_cols;
} CSRMatrix;


void ReadMMtoCSR(const char *filename, CSRMatrix *matrix);

int addition(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C);
int subtraction(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C);
int multiplication(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C);
int transpose(CSRMatrix *A, CSRMatrix *C);

void deallocateMatrix(CSRMatrix *matrix);

void printMatrix(CSRMatrix *matrix);

#endif
