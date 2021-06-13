#include <omp.h>
#include <stdio.h>

int main()
{
    /* 
    1) #pragma omp parallel: create a team of threads
    1)omp_get_thread_num() return the ID of thread
    2)omp_get_num_threads() return the number of thread of the team*/
    #pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
    return 0;
}