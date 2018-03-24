#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int *arr;
int Size;
int counter;
int sum = 0;

const int M = 2; // columns
const int K = 3; // rows
const int N = 2; // columns
int i = 0;
int j = 0;

int a[M][K] = {{1,0,2},
               {-1,3,1}};

int b[K][N] = {{3,1},
               {2,1},
               {1,0}};


int c[K][K];

void *runner(void *param); /* the thread */

struct v
{
    int row;
    int col;
};

int main(int argc, char *argv[])
{
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    pthread_t *threads = (pthread_t *) malloc(Size * sizeof(pthread_t));

    pthread_attr_init(&attr);

    for(i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            struct v *data = (struct v *)malloc(sizeof(struct v));
            data->row = i;
            data->col = j;

            pthread_create(&threads[i], &attr, runner, data);
            pthread_join(threads[i], NULL);
        }
    }

    for (int x = 0; x < M; x++)
    {
        for (int y = 0; y < M; y++)
        {
            cout << c[x][y] << "  ";
        }
        cout << endl;
    }

    return 0;
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param)
{
    struct v *args = (struct v *)(param);


    for (int cnt = 0; cnt < K; cnt++)
    {
        sum = sum + (a[args->row][cnt] * b[cnt][args->col]);
    }

    c[args->row][args->col] = sum;

    sum = 0;

    pthread_exit(0);
}
