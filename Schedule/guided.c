#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define N 1000
int main()
{
    int n_threads, i;

    /*
    Schedule allows you to create the scheme with which 
    the threads distribute the work of an iteration of a cycle.
    "guided": It has a scheduling policy very similar to dynamic mode, 
    except that the chunk size changes during program execution.
    */
    #pragma omp parallel for private(i) schedule(guided) num_threads(4)
    for(i=0; i<N; i++)
    {
        //wait i second
        sleep(i);
        printf("The thread %d has completed the iteration %d\n", omp_get_thread_num(), i);
    }
    printf("Tutti i thread hanno terminato!\n");
    return 0;
}