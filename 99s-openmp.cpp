#include <omp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int main()
{
    int count = 0, i;
    int parCount = 0;
    int const size = 10000000; // 10,000,000
    //int myArray [size];
    int *myArray = new int[size];
    double start_time, end_time;
    double omp_start_time, omp_end_time;



    //initialize random number generator
    srand((unsigned)time(NULL));

    // Initialize the array using random numbers
    for (i = 0; i < size; i++)
        myArray[i] = rand() % 100;

    //Serial Code
    start_time = omp_get_wtime();


    for (i = 0; i < size; i++)
        if (myArray[i] == 99)
            count++;

    end_time = omp_get_wtime();

    printf ("The serial code indicates that there are %d 99s in the array.\n", count);
    printf ("The serial code used %f seconds to complete the execution.\n\n", end_time - start_time);

    // Parallel Code (2 Threads)
    omp_set_num_threads(2);

    omp_start_time = omp_get_wtime();

#pragma omp parallel for private(i) shared(myArray)
    for (i = 0; i < size; i++)
    {
        if (myArray[i] == 99)
        {
#pragma omp atomic
            parCount++;
        }
    }

    omp_end_time = omp_get_wtime();

    printf ("The parallel (2 threads) code indicates that there are %d 99s in the array.\n", parCount);
    printf ("The parallel (2 threads) code used %f seconds to complete the execution.\n", omp_end_time - omp_start_time);
    cout << "Speedup: " << (end_time - start_time) / (omp_end_time - omp_start_time) << "\n\n";


    // Parallel Code (4 Threads)
    parCount = 0;

    omp_set_num_threads(4);

    omp_start_time = omp_get_wtime();

#pragma omp parallel for private(i) shared(myArray)
    for (i = 0; i < size; i++)
    {
        if (myArray[i] == 99)
        {
#pragma omp atomic
            parCount++;
        }
    }

    omp_end_time = omp_get_wtime();

    printf ("The parallel (4 threads) code indicates that there are %d 99s in the array.\n", parCount);
    printf ("The parallel (4 threads) code used %f seconds to complete the execution.\n", omp_end_time - omp_start_time);
    cout << "Speedup: " << (end_time - start_time) / (omp_end_time - omp_start_time) << "\n\n";

    // Parallel Code (8 Threads)
    parCount = 0;
    omp_set_num_threads(8);

    omp_start_time = omp_get_wtime();

#pragma omp parallel for private(i) shared(myArray)
    for (i = 0; i < size; i++)
    {
        if (myArray[i] == 99)
        {
#pragma omp atomic
            parCount++;
        }
    }

    omp_end_time = omp_get_wtime();

    printf ("The parallel (8 threads) code indicates that there are %d 99s in the array.\n", parCount);
    printf ("The parallel (8 threads) code used %f seconds to complete the execution.\n", omp_end_time - omp_start_time);
    cout << "Speedup: " << (end_time - start_time) / (omp_end_time - omp_start_time) << "\n\n";

    delete [] myArray;

    return 0;
}