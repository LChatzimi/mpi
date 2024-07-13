#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_vector_multiply(int n, double *A, double *x, double *y) {
    for (int i = 0; i < n; i++) {
        y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            y[i] += A[i * n + j] * x[j]; 
        }
    }
}

int main(int argc, char *argv[]) {
    int n;
    double *A, *x, *y;
    struct timespec start_time, end_time;

    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    
    A = (double *)malloc(n * n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));

    if (A == NULL || x == NULL || y == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = rand() % 100;  // Random values for the matrix
        }
    }

    for (int i = 0; i < n; i++) {
        x[i] = rand() % 100;  
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Initialization time: %f seconds\n", (double)(end_time.tv_sec - start_time.tv_sec) +
                                               (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9);

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    matrix_vector_multiply(n, A, x, y);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Execution time: %f seconds\n", (double)(end_time.tv_sec - start_time.tv_sec) +
                                           (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9);

    free(A);
    free(x);
    free(y);

    return 0;
}
