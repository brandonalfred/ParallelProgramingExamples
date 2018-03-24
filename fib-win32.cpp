#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>

using namespace std;

int *arr;
int Size;
int counter;

DWORD WINAPI fib(LPVOID param);

int main(int argc, char *argv[])
{
    Size = atoi(argv[1]) + 1;
    arr = (int *)malloc(Size * sizeof(int));
    DWORD ThreadId;
    HANDLE ThreadHandle;

    HANDLE threads[Size];

    if (argc != 2)
    {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 45)
    {
        cout << "value must be greater than 0 and less than/equal to 45" << endl;
        return -1;
    }

    for (counter = 0; counter < Size; counter++)
    {
        threads[counter] = CreateThread( NULL, 0, fib, &threads[counter], 0, &ThreadId);
        if(threads[counter] != NULL)
        {
            WaitForSingleObject(threads[counter], INFINITE);
            CloseHandle(ThreadHandle);
        }
    }

    for(int i = 0; i < Size; i++)
        cout << arr[i] << endl;

    return 0;
}

DWORD WINAPI fib(LPVOID param)
{
    if (counter == 0)
    {
        arr[counter] = 0;
        return 0;
    }

    if (counter == 1)
    {
        arr[counter] = 1;
        return 0;
    }
    else
    {
        arr[counter] = arr[counter - 1] + arr[counter - 2];
        return 0;
    }
    return 0;
}
