#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int binarySearch(int left, int right, int t, int token, int *a);

int main()
{
    int i, token, n, t = 2, result, *a;
    printf("Enter the size of the vector a: ");
    scanf("%d", &n);
    a = (int *)malloc(n * sizeof(int));
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        a[i] = 2 * i;
        printf("[%d]\t", a[i]);
    }
    printf("\nEnter the number to search: ");
    scanf("%d", &token);
    result = binarySearch(0, n-1, t, token, a);

    if (result < 0)
        printf("\nThe number not is in the vector.");
    else
        printf("\nThe number is in the position: %d\n", result+1);

    free(a);
    return 0;
}

int binarySearch(int left, int right, int t, int token, int *a)
{
    int result=-1;
    //Size is the sub-portion that each individual thread must check
    int size = (right - left + 1 ) / 2; 
    //CCheck if the thread is looking on only one field
    if(size == 0){
        if(a[left] != token)
        {
            //if token was not found return -1
            return -1;
        }else{
            //else return the value of element
            return left;
        }
    }
    omp_set_num_threads(t);
    omp_set_nested(1);
    #pragma omp parallel shared(a, token, left, right, size)
    {
        //Calculates the extremes that each thread must have, using the value of the id
        int id = omp_get_thread_num();
        int leftThread = left + id * size;
        int rightThread = leftThread + size - 1;
        if( id == t-1)
            rightThread = right;
        /*If the thread finds it checks that the key is within its range,
        then it calls the same function with the updated values of its portion*/
        if(a[leftThread] <= token && a[rightThread] >= token)
        {
            result = binarySearch(leftThread, rightThread, t, token, a);
        }
    }
}
