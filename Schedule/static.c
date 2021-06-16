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
    "static": means that iterations blocks are mapped statically to the 
    execution threads in a round-robin fashion. The nice thing with static scheduling is that 
    OpenMP run-time guarantees that if you have two separate loops with the same number 
    of iterations and execute them with the same number of threads using static scheduling,
    */
    #pragma omp parallel for private(i) schedule(static) num_threads(4)
    for(i=0; i<16; i++)
    {
        //wait i second
        sleep(i);
        printf("The thread %d has completed the iteration %d\n", omp_get_thread_num(), i);
    }
    printf("All threads have ended!\n");
    return 0;
}
