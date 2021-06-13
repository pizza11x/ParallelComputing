//OMP is a librery for Multi Processing
#include <omp.h>
#include <stdio.h>

int main()
{
    /* 
    - #pragma omp parallel: create a team of threads
    - omp_get_thread_num() return the ID of thread
    - omp_get_num_threads() return the number of thread of the team
    */
    #pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
    return 0;
}
