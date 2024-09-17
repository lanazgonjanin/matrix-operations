// ChatGPT was used
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

void ReadMMtoCSR(const char *filename, CSRMatrix *matrix)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    do {
        read = getline(&line, &len, file);
        if (read == EOF) 
        {
            printf("Invalid mtx file.\n");
            exit(EXIT_FAILURE);
        }
    } while (line[0] == '%');

    int num_rows, num_cols, num_non_zeros;
    sscanf(line, "%d %d %d", &num_rows, &num_cols, &num_non_zeros);

    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;
    matrix->num_non_zeros = num_non_zeros;

    matrix->csr_data = (double *)malloc(num_non_zeros * sizeof(double));
    matrix->col_ind = (int *)malloc(num_non_zeros * sizeof(int));
    matrix->row_ptr = (int *)malloc((num_rows + 1) * sizeof(int));

    int *col1 = (int *)malloc(num_non_zeros * sizeof(int));
    int *col2 = (int *)malloc(num_non_zeros * sizeof(int));
    double *col3 = (double *)malloc(num_non_zeros * sizeof(double));

    for (int i = 0; i < num_non_zeros; i++) 
    {
        int row, col;
        double value = 1.0;

        read = getline(&line, &len, file);

        int scan_entries = sscanf(line, "%d %d %lf", &row, &col, &value);

        if (scan_entries < 3) 
        {
            value = 1.0;
        }

        col1[i] = row - 1;
        col2[i] = col - 1;
        col3[i] = value;
    }

    int *num_nonzeros_per_row = (int *)calloc(num_rows, sizeof(int));

    for (int j = 0; j < num_non_zeros; j++) 
    {
        num_nonzeros_per_row[col1[j]] = num_nonzeros_per_row[col1[j]] + 1;
    }

    matrix->row_ptr[0] = 0;

    for (int k = 1; k <= num_rows; k++) 
    {
        matrix->row_ptr[k] = matrix->row_ptr[k - 1] + num_nonzeros_per_row[k - 1];
    }

    int *index = (int *)calloc(num_rows, sizeof(int));

    for (int l = 0; l < num_non_zeros; l++) 
    {
        int row = col1[l];
        int d = matrix->row_ptr[row] + index[row];

        matrix->csr_data[d] = col3[l];
        matrix->col_ind[d] = col2[l];
        index[row] = index[row] + 1;
    }

    free(col1);
    free(col2);
    free(col3);
    free(num_nonzeros_per_row);
    free(index);

    if (line != NULL) 
    {
        free(line);
    }
    
    fclose(file);
}

void deallocateMatrix(CSRMatrix *matrix)
{
    if (matrix->csr_data != NULL)
    {
        free(matrix->csr_data);
    }

    if (matrix->col_ind != NULL)
    {
        free(matrix->col_ind);
    }
    
    if (matrix->row_ptr != NULL)
    {
        free(matrix->row_ptr);
    }
}

void printMatrix(CSRMatrix *matrix)
{
    printf("Number of non-zeros: %d\n", matrix->num_non_zeros);

    printf("Row Pointer: ");
    for (int m = 0; m <= matrix->num_rows; m++) 
    {
        printf("%d ", matrix->row_ptr[m]);
    }
    printf("\n");

    printf("Column Index: ");
    for (int n = 0; n < matrix->num_non_zeros; n++) 
    {
        printf("%d ", matrix->col_ind[n]);
    }
    printf("\n");

    printf("Values: ");
    for (int p = 0; p < matrix->num_non_zeros; p++) 
    {
        printf("%.10f ", matrix->csr_data[p]);
    }
    printf("\n");
}

int addition(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C)
{
    if (A->num_cols != B->num_cols || A->num_rows != B->num_rows)
    {
        printf("\n");
        printf("The matrices are not compatible for addition.\n");
        return 0;
    }

    C->num_rows = A->num_rows;
    C->num_cols = A->num_cols;
    C->row_ptr = (int *)malloc((C->num_rows + 1) * sizeof(int));
    C->csr_data = (double *)malloc((A->num_non_zeros + B->num_non_zeros) * sizeof(double));
    C->col_ind = (int *)malloc((A->num_non_zeros + B->num_non_zeros) * sizeof(int));

    int C_num_nonzeros = 0;
    C->row_ptr[0] = 0;

    for (int i = 0; i < A->num_rows; i++)
    {
        int A_first_index = A->row_ptr[i];
        int A_last_index = A->row_ptr[i + 1];
        int B_first_index = B->row_ptr[i];
        int B_last_index = B->row_ptr[i + 1];

        while (A_first_index < A_last_index && B_first_index < B_last_index)
        {
            if (A->col_ind[A_first_index] == B->col_ind[B_first_index])
            {
                double s = A->csr_data[A_first_index] + B->csr_data[B_first_index];

                if (s != 0)
                {
                    C->csr_data[C_num_nonzeros] = s;
                    C->col_ind[C_num_nonzeros] = A->col_ind[A_first_index];
                    C_num_nonzeros = C_num_nonzeros + 1;
                }

                A_first_index = A_first_index + 1;
                B_first_index = B_first_index + 1;
            }
            else if (A->col_ind[A_first_index] < B->col_ind[B_first_index])
            {
                C->csr_data[C_num_nonzeros] = A->csr_data[A_first_index];
                C->col_ind[C_num_nonzeros] = A->col_ind[A_first_index];
                C_num_nonzeros = C_num_nonzeros + 1;
                A_first_index = A_first_index + 1;
            }
            else
            {
                C->csr_data[C_num_nonzeros] = B->csr_data[B_first_index];
                C->col_ind[C_num_nonzeros] = B->col_ind[B_first_index];
                C_num_nonzeros = C_num_nonzeros + 1;
                B_first_index = B_first_index + 1;
            }
        }

        while (A_first_index < A_last_index)
        {
            C->csr_data[C_num_nonzeros] = A->csr_data[A_first_index];
            C->col_ind[C_num_nonzeros] = A->col_ind[A_first_index];
            C_num_nonzeros = C_num_nonzeros + 1;
            A_first_index = A_first_index + 1;
        }

        while (B_first_index < B_last_index)
        {
            C->csr_data[C_num_nonzeros] = B->csr_data[B_first_index];
            C->col_ind[C_num_nonzeros] = B->col_ind[B_first_index];
            C_num_nonzeros = C_num_nonzeros + 1;
            B_first_index = B_first_index + 1;
        }

        C->row_ptr[i + 1] = C_num_nonzeros;
    }

    C->num_non_zeros = C_num_nonzeros;

    return 1;
}

int subtraction(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C)
{
    if (A->num_cols != B->num_cols || A->num_rows != B->num_rows)
    {
        printf("\n");
        printf("The matrices are not compatible for subtraction.\n");
        return 0;
    }

    C->num_rows = A->num_rows;
    C->num_cols = A->num_cols;
    C->row_ptr = (int *)malloc((C->num_rows + 1) * sizeof(int));
    C->csr_data = (double *)malloc((A->num_non_zeros + B->num_non_zeros) * sizeof(double));
    C->col_ind = (int *)malloc((A->num_non_zeros + B->num_non_zeros) * sizeof(int));

    int C_num_nonzeros = 0;
    C->row_ptr[0] = 0;

    for (int i = 0; i < A->num_rows; i++)
    {
        int A_first_index = A->row_ptr[i];
        int A_last_index = A->row_ptr[i + 1];
        int B_first_index = B->row_ptr[i];
        int B_last_index = B->row_ptr[i + 1];

        while (A_first_index < A_last_index && B_first_index < B_last_index)
        {
            if (A->col_ind[A_first_index] == B->col_ind[B_first_index])
            {
                double difference = A->csr_data[A_first_index] - B->csr_data[B_first_index];

                if (difference != 0)
                {
                    C->csr_data[C_num_nonzeros] = difference;
                    C->col_ind[C_num_nonzeros] = A->col_ind[A_first_index];
                    C_num_nonzeros = C_num_nonzeros + 1;
                }

                A_first_index = A_first_index + 1;
                B_first_index = B_first_index + 1;
            }
            else if (A->col_ind[A_first_index] < B->col_ind[B_first_index])
            {
                C->csr_data[C_num_nonzeros] = A->csr_data[A_first_index];
                C->col_ind[C_num_nonzeros] = A->col_ind[A_first_index];
                C_num_nonzeros = C_num_nonzeros + 1;
                A_first_index = A_first_index + 1;
            }
            else
            {
                C->csr_data[C_num_nonzeros] = -(B->csr_data[B_first_index]);
                C->col_ind[C_num_nonzeros] = B->col_ind[B_first_index];
                C_num_nonzeros = C_num_nonzeros + 1;
                B_first_index = B_first_index + 1;
            }
        }

        while (A_first_index < A_last_index)
        {
            C->csr_data[C_num_nonzeros] = A->csr_data[A_first_index];
            C->col_ind[C_num_nonzeros] = A->col_ind[A_first_index];
            C_num_nonzeros = C_num_nonzeros + 1;
            A_first_index = A_first_index + 1;
        }

        while (B_first_index < B_last_index)
        {
            C->csr_data[C_num_nonzeros] = -(B->csr_data[B_first_index]);
            C->col_ind[C_num_nonzeros] = B->col_ind[B_first_index];
            C_num_nonzeros = C_num_nonzeros + 1;
            B_first_index = B_first_index + 1;
        }

        C->row_ptr[i + 1] = C_num_nonzeros;
    }
    
    C->num_non_zeros = C_num_nonzeros;

    return 1;
}

int multiplication(CSRMatrix *A, CSRMatrix *B, CSRMatrix *C)
{
    if (A->num_cols != B->num_rows)
    {
        printf("\n");
        printf("The matrices are not compatible for multiplication.\n");
        return 0;
    }

    C->num_rows = A->num_rows;
    C->num_cols = A->num_cols;
    C->row_ptr = (int *)malloc((C->num_rows + 1) * sizeof(int));
    C->csr_data = (double *)malloc((A->num_non_zeros + B->num_non_zeros) * sizeof(double));
    C->col_ind = (int *)malloc((A->num_non_zeros + B->num_non_zeros) * sizeof(int));

    int *C_col_ind = (int *)malloc(B->num_cols * sizeof(int));
    double *C_csr_data = (double *)malloc(B->num_cols * sizeof(double));

    int C_num_nonzeros = 0;
    C->row_ptr[0] = 0;

    for (int i = 0; i < A->num_rows; i++)
    {
        for (int j = 0; j < B->num_cols; j++)
        {
            C_col_ind[j] = -1;
            C_csr_data[j] = 0.0;
        }

        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
        {
            int A_nonzero_col = A->col_ind[j];
            double A_nonzero_value = A->csr_data[j];

            for (int k = B->row_ptr[A_nonzero_col]; k < B->row_ptr[A_nonzero_col + 1]; k++)
            {
                int B_nonzero_col = B->col_ind[k];
                double B_nonzero_value = B->csr_data[k];

                if (C_col_ind[B_nonzero_col] == -1)
                {
                    C_col_ind[B_nonzero_col] = B_nonzero_col;
                }
                C_csr_data[B_nonzero_col] += A_nonzero_value * B_nonzero_value;
            }
        }

        for (int j = 0; j < B->num_cols; j++)
        {
            if (C_col_ind[j] != -1 && C_csr_data[j] != 0)
            {
                C->csr_data[C_num_nonzeros] = C_csr_data[j];
                C->col_ind[C_num_nonzeros] = C_col_ind[j];
                C_num_nonzeros = C_num_nonzeros + 1;
            }
        }

        C->row_ptr[i + 1] = C_num_nonzeros;
    }
    
    C->num_non_zeros = C_num_nonzeros;
    C->csr_data = (double *)realloc(C->csr_data, C_num_nonzeros * sizeof(double));
    C->col_ind = (int *)realloc(C->col_ind, C_num_nonzeros * sizeof(int));

    free(C_col_ind);
    free(C_csr_data);

    return 1;
}

int transpose(CSRMatrix *A, CSRMatrix *C)
{
    C->num_rows = A->num_cols;
    C->num_cols = A->num_rows;
    C->num_non_zeros = A->num_non_zeros;
    C->csr_data = (double *)malloc(A->num_non_zeros * sizeof(double));
    C->col_ind = (int *)malloc(A->num_non_zeros * sizeof(int));
    C->row_ptr = (int *)malloc((C->num_rows + 1) * sizeof(int));

    int *num_nonzeros_per_col = (int *)calloc(C->num_rows, sizeof(int));

    for (int i = 0; i < A->num_non_zeros; i++)
    {
        num_nonzeros_per_col[A->col_ind[i]]++;
    }

    C->row_ptr[0] = 0;

    for (int i = 1; i <= C->num_rows; i++)
    {
        C->row_ptr[i] = C->row_ptr[i - 1] + num_nonzeros_per_col[i - 1];
    }

    int *cur_pos = (int *)calloc(C->num_rows, sizeof(int));

    for (int i = 0; i < C->num_rows; i++)
    {
        cur_pos[i] = C->row_ptr[i];
    }

    for (int i = 0; i < A->num_rows; i++)
    {
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
        {
            int col = A->col_ind[j];
            double val = A->csr_data[j];
            int pos = cur_pos[col];

            C->csr_data[pos] = val;
            C->col_ind[pos] = i;
            cur_pos[col]++;
        }
    }

    free(num_nonzeros_per_col);
    free(cur_pos);
    
    return 1;
}