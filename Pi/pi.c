#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define quantity 10000000
/* To calculate pi, the integral defined between 0 and 1 of (4/1 + x ^ 2) dx = pi was used
    Numerically, this is nothing more than 
    the summation of i which goes from 1 to N of (4/1 + [(i - 1/2) h] ^ 2) = pi
*/
int main()
{
    long int i, n = quantity;
    double x, dx, f, sum, pi;
    printf("Number of intervals: %ld\n", n);
    sum=0.0;

    dx = 1.0/(double)n;
    /*
    The for construct specifies that the iterations of the contained loop 
    should be distributed across team threads
    */
    #pragma omp parallel for private (x, f, i) shared(dx, n) reduction(+:sum)
    for(i=1; i<=n; i++)
    {
        x = dx * ((double)(i - 0.5));
        f = 4.0 / (1.0+x*x);
        sum+=f;
    }

    pi=dx*sum;
    printf("PI %.24f\n", pi);

    return 0;
}