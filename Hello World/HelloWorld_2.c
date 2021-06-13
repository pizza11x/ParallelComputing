#include <omp.h>
#include <stdio.h>

int main()
{
    int id_thread, num_threads;
    /*
    -id_thread: it must be private, that is, it must take on a different value for each 
    thread that will execute the parallel piece of code.
    -num_threads: It can be left shared so it is left unique
    */
    #pragma omp parallel private(id_thread), shared(num_threads)
    {
        id_thread = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        printf("Hello from thread %d, nthread %d\n", id_thread, num_threads);
    }
    return 0;
}