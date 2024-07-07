#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double estimate_pi(long long int num_throws) {
    long long int circle_points = 0;
    unsigned int seed = (unsigned int)time(NULL);
    for (long long int i = 0; i < num_throws; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
        if (x * x + y * y <= 1.0) {
            circle_points++;
        }
    }
    return 4.0 * circle_points / num_throws;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_throws>\n", argv[0]);
        return -1;
    }

    long long int num_throws = atoll(argv[1]);
    srand(time(NULL));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    double pi_estimate = estimate_pi(num_throws);
     clock_gettime(CLOCK_MONOTONIC, &end);

    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;

    printf("Estimated Pi: %f\n", pi_estimate);
    printf("Execution Time: %f seconds\n", time_spent);

    return 0;
}