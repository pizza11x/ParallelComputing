#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

/* 
This program allows you to sort an array of different sizes.
This algorithm is optimized as it avoids contention by using two variables for exchanges.
A thread enters the parallel section only if these two fields are reset
*/
void oddEvenSort(int *a, int size);

int main(){
   int size, i;
   int *a;

   printf("Enter the size of the vector: "); 
   scanf("%d", &size);

    a = (int *)malloc(size*sizeof(int));
    srand(time(NULL));
    for(i=0; i<size; i++)
    {
        a[i]=1+rand()%100;
        printf("[%d]\t", a[i]);
    }
    oddEvenSort(a, size);
    printf("\n");
    for(i=0; i<size; i++)
    {
        printf("[%d]\t", a[i]);
    }
    return 0;
}

void oddEvenSort(int *a, int size)
{
    //sw0 and sw1 are variables to control exchanges
    int sw0=0, sw1 = 0, i = 0, t= 0, temp;
   
   //It runs the loop only if the odd part is completely sorted
    while(!sw1)
    {
       
        sw0=1;
        sw1=1;
        #pragma omp parallel shared(a, size, sw0, sw1, t) private(temp, i)
        {
           //Even part
            #pragma omp for
            for(i=0; i<size-1; i+=2)
            {
                if(a[i]>a[i+1])
                {
                    temp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = temp;
                    sw0=0;
                }
            }
           /*
           If you have traded on the even side, then you do the odd side as well
           and if this is the first time the loop has run
           */
            if(!sw0 || !t)
            {
                #pragma omp for
                for(i=1; i<size -1; i+=2)
                {
                    if(a[i] > a[i+1])
                    {
                        temp = a[i];                    
                        a[i] = a[i+1];
                        a[i+1] = temp;
                        sw1=0;
                    }
                }
               //Sets that the cycle has run at least once.
               t = 1;
            }
        }
    }
}
