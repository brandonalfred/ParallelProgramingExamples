#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int *arr;
int Size;
int counter;

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{

    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    if (argc != 2)
    {
        fprintf(stderr,"usage: a.out <integer value>\n");
        /*exit(1);*/
        return -1;
    }

    if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 45)
    {
        //fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        cout << "value must be greater than 0 and less than/equal to 45" << endl;
        /*exit(1);*/
        return -1;
    }

    Size = atoi(argv[1]) + 1;
    arr = (int *)malloc(Size * sizeof(int));
    pthread_t *threads = (pthread_t *) malloc(Size * sizeof(pthread_t));

/* get the default attributes */
    pthread_attr_init(&attr);

    for (counter = 0; counter < Size; counter++)
    {
        pthread_create(&threads[counter], &attr, runner, NULL);
        pthread_join(threads[counter], NULL);
    }

    for(int i = 0; i < Size; i++)
        cout << arr[i] << endl;

    return 0;
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param)
{
    cout << "in child thread\n";

    if (counter == 0)
    {
        arr[counter] = 0;
        pthread_exit(0);
    }                           // first fib term

    if (counter == 1)
    {
        arr[counter] = 1;
        pthread_exit(0);
    }                           // seconed fib term
    else
    {
        arr[counter] = arr[counter - 1] + arr[counter - 2];
        pthread_exit(0);        // thread exit.
    }
}