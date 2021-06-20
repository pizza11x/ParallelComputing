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
    /*
    We pass the following values to the function:
    - the far left index (0)
    - the far right index (n-1)
    - the number of threads
    - the token to search for
    - vector A
    */
    result = binarySearch(0, n - 1, t, token, a);

    if (result < 0)
        printf("\nThe number not is in the vector.");
    else
        printf("\nThe number is in the position: %d\n", result+1);

    return 0;
}

int binarySearch(int left, int right, int t, int token, int *a)
{
    int index = -1, i;
    //Size, is the size of the sub-portion each thread must work on
    int size = (right - left + 1) / 2;
    omp_set_num_threads(t);
    omp_set_nested(1);
    #pragma omp parallel shared(a, token, left, size, index)
    {
        int id = omp_get_thread_num();
        /*
        leftThread is the leftmost index on which each thread must work. 
        It is calculated by adding to the index passed to the function the product between 
        the id of the current thread and the size of its portion of the vector
        */
        int leftThread = left + id * size;
        /*
        rightThread is the rightmost index on which each thread must work. 
        it is calculated from the sum of its leftThread with its sub-portion size -1
        */
        int rightThread = leftThread + size - 1;
        int middleThread;
        
        /*
        the while loop must be executed until the portions of the vector are greater than 1 and therefore the extreme left 
        is less than or equal to the extreme right
        */
        while (leftThread <= rightThread)
        {
            middleThread = (rightThread + leftThread) / 2;
            if (a[middleThread] == token)
            {
                /*
                If the element in the median position is equal to the token 
                then the value is stored, and enables the while to exit
                */
                index = middleThread;
                leftThread = rightThread + 1;
            }
            else if (token < a[middleThread])
            {
                /*
                Otherwise if the token is less than the element in the median position, 
                rightThread becomes median-1
                */
                rightThread = middleThread - 1;
            }
            else
            {
                /*
                Otherwise if the token is greater than the element in the median position, 
                leftThread becomes median+1
                */
                leftThread = middleThread + 1;
            }
        }
    }

    return index;
}
