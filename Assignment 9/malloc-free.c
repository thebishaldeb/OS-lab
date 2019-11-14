#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *myOwnMalloc(size_t size)
{
    void *p = sbrk(0);
    void *request = sbrk(size);
    if (request == (void *)-1)
    {
        return NULL;
    }
    else
    {
        assert(p == request);
        return p;
    }
}

int main()
{
    int i;
    int *arr = (int *)myOwnMalloc(sizeof(int) * 10);
    for (i = 0; i < 10; i++)
    {
        arr[i] = i;
        printf("%d\n", arr[i]);
    }
    return 0;
}