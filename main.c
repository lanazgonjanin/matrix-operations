#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main(int argc, char *argv[]) 
{
	if (argc != 5)
    {
        printf("Incorrect number of inputs. Please enter the first mtx file, the second mtx file, the operation, and the print statement.\n");
        return 1;
    }

	const char *filename1 = argv[1];
	const char *filename2 = argv[2];
	const char *operation = argv[3];
	const int print = atoi(argv[4]);

	CSRMatrix A;
	ReadMMtoCSR(filename1, &A);

	CSRMatrix B;
	ReadMMtoCSR(filename2, &B);

	if (print == 1)
	{
		printf("The following is the CSR format of the first matrix.\n");
		printMatrix(&A);
		printf("\n");
		printf("The following is the CSR format of the second matrix.\n");
		printMatrix(&B);
	}

	CSRMatrix C;
	int success = 0;

	clock_t start_time, end_time;
    double cpu_time_used;

	if (strcmp(operation, "addition") == 0)
	{
		success = addition(&A, &B, &C);
	}
	else if (strcmp(operation, "subtraction") == 0)
	{
		success = subtraction(&A, &B, &C);
	}
	else if (strcmp(operation, "multiplication") == 0)
	{
    	start_time = clock();

		success = multiplication(&A, &B, &C);

		end_time = clock();
		cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	}
	else if (strcmp(operation, "transpose") == 0)
	{
		success = transpose(&A, &C);
	}
	else
	{
		printf("\n");
		printf("Invalid input. Please re-run and specify the correct operation.\n");
	}

	if (success == 1 && print == 1)
	{
		printf("\n");
		printf("The following is the CSR format of the computed matrix.\n");
		printMatrix(&C);

		if (strcmp(operation, "multiplication") == 0)
		{
			printf("\n");
			printf("CPU time: %f seconds\n", cpu_time_used);
		}
	}

	deallocateMatrix(&A);
	deallocateMatrix(&B);
	deallocateMatrix(&C);

	return 0;
}
