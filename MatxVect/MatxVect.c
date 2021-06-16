#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

/*
This is a function to calculate the product of a matrix by a vector.
You have to call it in a main program.


-n: rows
-m: columns
*/

double *matxvet(int n, int m, double *vect, double **matrix)
{
    int i, j;
    double *sol;
    /*the solution vector must be allocated by the number of rows*/
    sol = (double *)calloc(n, sizeof(double));

    /*
    -dafault(none): Specifies the behavior of unscoped variables in a parallel region.
    only the index i and j are private.

    */
    #pragma omp parallel for default(none) shared(sol, matrix, vect, m, n) private(i, j)
    for (i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
            sol[i] += matrix[i][j]*vect[j];
    }

    return sol;

}