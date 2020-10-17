#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 10

int main(int argc, char **argv)
{

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel num_threads(4)
{
    printf("hello from %d, %f\n", omp_get_thread_num(), omp_get_wtime());
}

    return 0;
}

