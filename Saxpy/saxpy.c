#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

/*
The saxpy problem is calculated as follows:

R[i] = (alpha * A * b) + (a * beta)

where:
-A is a matrix NxM,
-b is a vector of dimension M,
-a is a vector of dimension N,
-alpha and beta are two scalars,
-R is a vector that will contain the "i" results.

subsequently we have to make the product of the elements of the vector R.
*/

int main(){
    int i, j, alpha, beta, t, n, m;
    double *A, *b, *a, *R, p=1, t0, t1, temptot;
    /*
    We ask in input the number of threads to use, it is recommended to use an even number of threads, 
    in fact if you enter an odd number, the program exits with an error
    */
    printf("Insert the number of threads: ");
    scanf("%d", &t);
    if((t%2) != 0)
        exit(EXIT_FAILURE);
    //We ask in input the data of the problem
    printf("Insert the rows of the A matrix : ");
    scanf("%d", &n);
    printf("Insert the columns of the A matrix: ");
    scanf("%d", &m);
    printf("Insert the value of alpha : ");
    scanf("%d", &alpha);
    printf("Insert the value of beta: ");
    scanf("%d", &beta);

    /*
    Divisibility check, if the problems is not divisibility for the number of threads,
    the program exit with an error
    */
    if((n%t) != 0)
        exit(EXIT_FAILURE);
    
    //Dynamic allocation of the matrix and vectors
    A = (double *)malloc((n*m)*sizeof(double));
    b = (double *)malloc(m*sizeof(double));
    a = (double *)malloc(n*sizeof(double));
    R = (double *)malloc(n*sizeof(double));
    
    //Filling and printing of the matrix and the vectors
    srand(time(NULL));
    for(i=0; i<n; i++){
        a[i] = (double)((rand()%1000)+1)/1000;
        for(j=0; j<m; j++){
            A[(i*m)+j] = (double)((rand()%1000)+1)/1000;
            b[j] = (double)((rand()%1000)+1)/1000;
        }
    }
    printf("\nThe matrix A is:\n");
    for(i=0; i < n; i++){
        for(j=0; j < m; j++){
            printf("[%f]\t", A[(i*m)+j]);
        }
        printf("\n");
    }
    printf("\nThe vector b is\n");
    for(i=0; i < m; i++){
            printf("[%f]\n", b[i]);
    }
    printf("\nThe vector a is\n");
    for(i=0; i < n; i++){
            printf("[%f]\t", a[i]);
    }
    //Let's take the time of the sequentially performed part
    t0 = omp_get_wtime();

    #pragma omp parallel for schedule(static) shared(n,m,A,b,a,R,alpha,beta) private(i,j) num_threads(t)
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            /*
            Calculate the first part of the problem, then insert in the i-th position 
            the sum of the products of alpha * A[i][j] * b[j]
            */
            R[i]+=alpha*A[(i*m)+j]*b[j];
        }
        /*
        Calculate the second part of the problem, we add the i-th position of R
        (hence i-th result of the first part of the problem) with the product beta * a[i]
        */
        R[i]+=(a[i]*beta);
    }
    //Calculate the product of the elements of R. 
    #pragma omp parallel for shared(R,n,a) private(i) reduction(*:p) num_threads(t)
    for(i=0; i<n; i++)
        p=p*R[i];

    //Calculate the time performed in parallel
    t1=omp_get_wtime();
    //Calculate the Elapsed time
    temptot=t1-t0;

    //Stamp the R vector
    printf("\n\nThe vector R is\n");
    for(i=0; i < n; i++){
            printf("[%f]\t", R[i]);
    }

    //Stamp the result and the Elapsed time.
    printf("\n\nThe result is: %f\n", p);
    printf("\nElapsed Time: %lfs \n", temptot);

    //Free memory
    free(A);
    free(b);
    free(a);
    free(R);

    return 0;
}
