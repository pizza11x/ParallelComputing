#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    /*
    -quantity: quantity of numbers
    -threads: thread team working
    -localQuantity: amount of numbers each thread must add up
    -rest: Calculated to check if it is exactly divisible by the number of threads
    -step: It allows each core to know which elements it needs to deal with
    -*container: container of numbers
    */
    int i, quantity, threads, localQuantity, rest, id, step;
    float sumtot, sum, *container;
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
    #pragma omp parallel private(sum, localQuantity, i, id, step) shared(sumtot,rest)
    {
       threads = omp_get_num_threads();
       localQuantity = quantity/threads;
       id = omp_get_thread_num();
       rest = quantity%threads;
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
       sum=0;
       for(i=0; i<localQuantity; i++)
       {
           sum = sum+container[i+localQuantity*omp_get_thread_num()+step];
       }
       sumtot = sumtot + sum;
    }
    printf("Somma totale: %f\n", sumtot);
    return 0;
}