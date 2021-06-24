#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    int *A, *R, i, j, p=5, N=9, sumRow=0, rows=(N/2), countRow;
    double t0, t1, t_tot;

    A=(int *)malloc((N*N)*sizeof(int));
    R=(int *)malloc(rows*sizeof(int));

    srand(time(NULL));
    printf("The matrix is: \n");
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            A[(i*N)+j] = (rand()%10)+1;
            printf("[%d]\t", A[(i*N)+j]);
        }
        printf("\n");
    }
    t0=omp_get_wtime();
    #pragma omp parallel shared(A,R,p,N) private(i,j, step,countRow) reduction(+:sumRow) num_threads(p)
    {
        int id = omp_get_thread_num();
        countRow = (id*2)+1;
        int localSize = N/p;
        for(j=0; j<localSize; j++)
        {
            for(i=0; i<N; i++){
                sumRow+=A[countRow*N+i];
            }
        }
        R[id]=sumRow;
        t1=omp_get_wtime();
    }
    printf("\nThe vector is: \n");
    for(i=0; i<rows; i++){
        printf("[%d]\t", R[i]);
    }
    t_tot=t1-t0;
    printf("\nTotal time: %f", t_tot);

    return 0;
}