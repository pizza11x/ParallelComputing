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
    int size = (right - left + 1) / 2;
    omp_set_num_threads(t);
    omp_set_nested(1);
#pragma omp parallel shared(a, token, left, size, index)
    {
        int id = omp_get_thread_num();
        int leftThread = left + id * size;
        int rightThread = leftThread + size - 1;
        int middleThread;

        while (leftThread <= rightThread)
        {
            middleThread = (rightThread + leftThread) / 2;
            if (a[middleThread] == token)
            {
                
                index = middleThread;
                leftThread = rightThread + 1;
            }
            else if (token < a[middleThread])
            {
                rightThread = middleThread - 1;
            }
            else
            {
                leftThread = middleThread + 1;
            }
        }
    }

    return index;
}