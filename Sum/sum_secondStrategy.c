#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{ 
    /*t0, t1, t_tot: they are variable to take the time.*/
    int i, quantity, threads, localQuantity, rest, id, step;
    float sumtot, sum, *container, t0, t1, t_tot;
    sumtot = 0;
    printf("Inserire N\n");
    scanf("%d", &quantity);
    /*Dynamic allocation based on how many numbers the user has chosen*/
    container = (float *)calloc(quantity, sizeof(float));
    printf("Inserire i numeri da sommare\n");
    for(i=0; i<quantity; i++)
    {
       scanf("%f", &container[i]);
    }

    t0 = omp_get_wtime();

    /*
    Reduction: Specifies that one or more private variables of each 
    thread are the subject of a shrink operation at the end of the parallel area.
    */
    #pragma omp parallel private(sum, localQuantity, i, id, step) shared(rest) reduction(+:sumtot)
    {
       threads = omp_get_num_threads();
       localQuantity = quantity/threads;
        rest = quantity%threads;
        id = omp_get_thread_num();

       /*If the amount of numbers to be added is not exactly divisible by the number of threads,
        more numbers must be assigned to the cores that have the smaller identifier than the rest, 
       in order to balance the number of operations to be performed.*/
       if( id < rest){
            localQuantity++;
            step = 0;
       }
       else{
           step = rest;
       }
       sum = 0;
       for(i=0; i<localQuantity; i++)
        {
         printf("sono %d, di %d: numeri %d, r=%d, passo=%d\n", id, threads, localQuantity, rest, step);
         sum = sum+container[i+localQuantity*omp_get_thread_num()+step];
        }
       sumtot+=sum;
       t1 = omp_get_wtime();
    }
    t_tot= t1-t0;
    printf("Somma totale: %f\n", sumtot);
    printf("Tempo totale: %f\n", t_tot);
    return 0;
}