#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void matrix_vector_multiply(int n, double *local_A, double *x, double *local_y, int local_n, int my_rank) {
    //   printf("LOCAL N = %d\n", local_n);

    for (int i = 0; i < local_n; i++) {
        local_y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            local_y[i] += local_A[j + n * i] * x[i]; 
            // printf("RANK %d, local_A[%d] = %f  * x[%d] = %f\n", my_rank, j + n * i, local_A[j + n * i], i, x[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    int n, comm_sz, my_rank, local_n;
    double *local_A, *x, *local_y;
    double start_time, end_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (argc != 2) {
        if (my_rank == 0) {
            printf("Usage: %s <n>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    n = atoi(argv[1]);
    local_n = n / comm_sz;
    
    local_A = (double *)malloc(local_n * n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    local_y = (double *)malloc(local_n * sizeof(double));
   

    if (my_rank == 0) {
        start_time = MPI_Wtime();
        srand(12347);
        unsigned int seed = (unsigned int)time(NULL);
        double *A = (double *)malloc(n * n * sizeof(double));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i * n + j] = rand_r(&seed) % 100;  // Random values for the matrix
                // printf("A[%d] = %f\n", i * n + j, A[i * n + j]);
            }
        }

        for (int i = 0; i < n; i++) {
            x[i] = rand_r(&seed) % 100;  
            // printf("x[%d] = %f\n", i, x[i]);
        }

        end_time = MPI_Wtime();
        printf("Initialization time: %f seconds\n", end_time - start_time);
        double *transposed_A = (double *)malloc(n * n * sizeof(double));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                transposed_A[j * n + i] = A[i * n + j];
            }
        }
      

        start_time = MPI_Wtime();
        MPI_Scatter(transposed_A, local_n * n, MPI_DOUBLE, local_A, local_n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(x, local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        free(transposed_A);
        free(A);
    } else {
        MPI_Scatter(NULL, local_n * n, MPI_DOUBLE, local_A, local_n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(NULL, local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    matrix_vector_multiply(n, local_A, x, local_y, local_n, my_rank);

    double *y = NULL;
    if (my_rank == 0) {
        y = (double *)malloc(n * sizeof(double));
    }

    MPI_Gather(local_y, local_n, MPI_DOUBLE, y, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   
    if (my_rank == 0) {
        // printf("Result vector y:\n");
        // for (int i = 0; i < n; i++) {
        //     printf("%f ", y[i]);
        // }
        // printf("\n");
        end_time = MPI_Wtime();
        free(y);
        printf("Execution time: %f seconds\n", end_time - start_time);
    }

    free(local_A);
    free(x);
    free(local_y);

    MPI_Finalize();
    return 0;
}
