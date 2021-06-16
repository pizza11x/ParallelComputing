#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
int main()
{
    int n_threads, i;

    /*
    Schedule allows you to create the scheme with which 
    the threads distribute the work of an iteration of a cycle.
    "dynamic": scheduling works on a "first come, first served" basis. In this way each thread 
    has an iteration, when it ends it will be assigned the next iteration
    */
    #pragma omp parallel for private(i) schedule(dynamic) num_threads(4)
    for(i=0; i<16; i++)
    {
        //wait i second
        sleep(i);
        printf("The thread %d has completed the iteration %d\n", omp_get_thread_num(), i);
    }
    printf("All threads have ended!!\n");
    return 0;
}
