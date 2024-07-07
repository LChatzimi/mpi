#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int monte_carlo_pi(long long int num_throws) {
     long long int circle_points = 0;
    unsigned int seed = (unsigned int)time(NULL);
    for (long long int i = 0; i < num_throws; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
        if (x * x + y * y <= 1.0) {
            circle_points++;
        }
    }
    return circle_points;
}

int main(int argc, char *argv[]) {
    int rank, size;
    long long int num_throws, local_throws, local_in_circle, total_in_circle;
    double pi_estimate;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: %s <num_throws>\n", argv[0]);
        }
        MPI_Finalize();
        return -1;
    }
    num_throws = atoll(argv[1]);

    MPI_Bcast(&num_throws, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);
    
    local_throws = num_throws / size;
    srand(time(NULL) + rank);

    start_time = MPI_Wtime();
    local_in_circle = monte_carlo_pi(local_throws);
    MPI_Reduce(&local_in_circle, &total_in_circle, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (rank == 0) {
        pi_estimate = (4.0 * total_in_circle) / num_throws;
        printf("Estimated value of Pi: %f\n", pi_estimate);
        printf("Execution time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
