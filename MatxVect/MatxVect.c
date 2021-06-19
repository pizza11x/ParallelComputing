#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h> 
/*
This is a function to calculate the product of a matrix by a vector.
You have to call it in a main program.
-n: rows
-m: columns
*/
double *matxvet(int n, int m, double *vect, double *matrix);

int main()
{
    int n, m, i, j;
    double *A;
    double *b;
    double *x;

    printf("Insert the rows of the A matrix : ");
    scanf("%d", &n);
    printf("Insert the columns of the A matrix: ");
    scanf("%d", &m);
    /*Allocation of matrix A with filling of random numbers */
    A = (double *)malloc((n*m)*sizeof(double ));
    srand(time(NULL)); 
    for(i=0; i < n; i++){
        for(j=0; j < m; j++){
            A[(i*m)+j]= (double)((rand()%1000)+1)/1000;
        }
    }
    /*Allocation of vector b and x with filling the vector x of random numbers*/
    b = (double *)malloc(n*sizeof(double));
    x = (double *)malloc(m*sizeof(double));
    for(i=0; i < m; i++){
            x[i] = (double)((rand()%1000)+1)/1000;
    }
    /*Stamp matrix  A*/
    printf("\nThe matrix A is:\n");
    for(i=0; i < n; i++){
        for(j=0; j < m; j++){
            printf("[%f]\t", A[(i*m)+j]);
        }
        printf("\n");
    }
    /*Stamp vector x*/
    printf("\nThe vector x is\n");
    for(i=0; i < m; i++){
            printf("[%f]\n", x[i]);
    }
    /*Calculate the solution vector with the function*/
    b = matxvet(n,m,x,A);
    /*stamp vector b*/
    printf("\nThe vector b is:\n");
    for(i=0; i < n; i++){
            printf("[%f]\t", b[i]);
    }
    free(x);
    free(b);
    free(A);
    return 0;

}



double *matxvet(int n, int m, double *vect, double *matrix)
{
    int i, j;
    double *sol;
    /*the solution vector must be allocated by the number of rows*/
    sol = (double *)malloc(n*sizeof(double));

    /*
    -dafault(none): Specifies the behavior of unscoped variables in a parallel region.
    only the index i and j are private.
    */
    #pragma omp parallel for default(none) shared(sol, matrix, vect, m, n) private(i, j)
    for (i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
            sol[i] += matrix[(i*m)+j]*vect[j];
    }

    return sol;

}
