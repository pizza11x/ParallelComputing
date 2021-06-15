#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define N 1000
#define CHUNK 10

int main()
{
    int n_threads, i;

    /*
    Schedule allows you to create the scheme with which 
    the threads distribute the work of an iteration of a cycle.
    "dynamic" with CHUNK: scheduling works on a "first come, first served" basis. In this way each thread 
    has an iteration, when it ends it will be assigned the next iterationin this way, each thread will be associated 
    with a predetermined number of iterations, so when it is finished it will have assigned a new chunk. 
    By increasing the size of the chunk, scheduling tends to static mode, while decreasing it, scheduling tends to dynamic
    */
    #pragma omp parallel for private(i) schedule(dynamic, CHUNK) num_threads(4)
    for(i=0; i<16; i++)
    {
        //wait i second
        sleep(i);
        printf("The thread %d has completed the iteration %d\n", omp_get_thread_num(), i);
    }
    printf("Tutti i thread hanno terminato!\n");
    return 0;
}