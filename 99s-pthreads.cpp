#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <pthread.h>

using namespace std;

void *runner_two(void *param); /* the thread */
void *runner_four(void *param); /* the thread */
void *runner_eight(void *param); /* the thread */

int counter = 0, i;
int const Size = 10000000; // 10,000,000
int *myArray = new int[Size];

int const max_two = 2;
int const max_four = 4;
int const max_eight = 8;

int threadCount_two[2] = {0, 0};
int threadCount_four[4] = {0, 0, 0, 0};
int threadCount_eight[8] = {0, 0, 0, 0, 0, 0, 0, 0};

pthread_t two_id[max_two];
pthread_t four_id[max_four];
pthread_t eight_id[max_eight];

int main()
{

    double seq_time, para_time;

    clock_t start, end;
    clock_t para_start, para_end;

    pthread_attr_t attr; /* set of attributes for the thread */

    pthread_attr_init(&attr);

    //initialize random number generator
    srand((unsigned) time(NULL));

    // Initialize the array using random numbers
    for (i = 0; i < Size; i++)
        myArray[i] = rand() % 100;

    //Serial Code
    start = clock();

    for (i = 0; i < Size; i++)
    {
        if (myArray[i] == 99)
            counter++;
    }


    end = clock();

    seq_time = double (end - start) / CLOCKS_PER_SEC;
    printf("\nThe serial code indicates that there are %d 99s in the array.\n", counter);
    printf("The serial code used %f seconds to complete the execution.\n\n", seq_time);


    // Parallel Code (2 threads)
    para_start = clock();

    int const arrSize = 2;
    int arr[arrSize] = {0, 1};

    for (int j = 0; j < arrSize; ++j)
    {
        pthread_create(&two_id[j], NULL, runner_two, &arr[j]);
    }

    for (int j = 0; j < arrSize; ++j)
    {
        pthread_join(two_id[j], NULL);
    }

    para_end = clock();

    int sum = 0;
    for (int k = 0; k < 2; ++k)
    {
        sum += threadCount_two[k];
    }

    para_time = double (para_end - para_start) / CLOCKS_PER_SEC;
    printf("\nThe parallel code (2 threads) indicates that there are %d 99s in the array.\n", sum);
    printf("The parallel code (2 threads) used %f seconds to complete the execution.\n", para_time);
    cout << "Speedup: " << seq_time / para_time << "\n\n";

    // Parallel Code (4 threads)
    para_start = clock();

    int const arrSize_four = 4;
    int arr_four[arrSize_four] = {0, 1, 2, 3};

    for (int j = 0; j < arrSize_four; ++j)
    {
        pthread_create(&four_id[j], NULL, runner_four, &arr_four[j]);
    }

    for (int j = 0; j < arrSize_four; ++j)
    {
        pthread_join(four_id[j], NULL);
    }

    para_end = clock();

    sum = 0;
    for (int k = 0; k < 4; ++k)
    {
        sum += threadCount_four[k];
    }

    para_time = double (para_end - para_start) / CLOCKS_PER_SEC;
    printf("\nThe parallel code (4 threads) indicates that there are %d 99s in the array.\n", sum);
    printf("The parallel code (4 threads) used %f seconds to complete the execution.\n", para_time);
    cout << "Speedup: " << seq_time / para_time << "\n\n";

    // Parallel Code (8 threads)
    para_start = clock();

    int const arrSize_eight = 8;
    int arr_eight[arrSize_eight] = {0, 1, 2, 3, 4, 5, 6, 7};

    for (int j = 0; j < arrSize_eight; ++j)
    {
        pthread_create(&eight_id[j], NULL, runner_eight, &arr_eight[j]);
    }

    for (int j = 0; j < arrSize_eight; ++j)
    {

        pthread_join(eight_id[j], NULL);
    }

    para_end = clock();

    sum = 0;
    for (int k = 0; k < 8; ++k)
    {
        sum += threadCount_eight[k];
    }

    para_time = double (para_end - para_start) / CLOCKS_PER_SEC;
    printf("\nThe parallel code (8 threads) indicates that there are %d 99s in the array.\n", sum);
    printf("The parallel code (8 threads) used %f seconds to complete the execution.\n", para_time);
    cout << "Speedup: " << seq_time / para_time << "\n\n";

    return 0;
}

void *runner_two(void *param)
{
    int x = *(int *)param;
    int tid = *(int *)param;

    int length_per_thread = Size / max_two;

    int starter = tid * length_per_thread;

    for (x = starter; x < (starter + length_per_thread); x++)
    {
        if (myArray[x] == 99)
        {
            threadCount_two[*(int *)param]++;
        }
    }

    pthread_exit(0);
}

void *runner_four(void *param)
{
    int x = *(int *)param;
    int tid = *(int *)param;

    int length_per_thread = Size / max_four;

    int starter = tid * length_per_thread;

    for (x = starter; x < (starter + length_per_thread); x++)
    {
        if (myArray[x] == 99)
        {
            threadCount_four[*(int *)param]++;
        }
    }

    pthread_exit(0);
}

void *runner_eight(void *param)
{
    int x = *(int *)param;
    int tid = *(int *)param;

    int length_per_thread = Size / max_eight;

    int starter = tid * length_per_thread;

    for (x = starter; x < (starter + length_per_thread); x++)
    {
        if (myArray[x] == 99)
        {
            threadCount_eight[*(int *)param]++;
        }
    }

    pthread_exit(0);
}