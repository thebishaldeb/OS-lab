#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int *var;

int main()
{
    var = mmap(NULL, sizeof(*var), PROT_READ | PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *var = 1;

    if (fork() == 0)
    {
        *var = 5;
        exit(EXIT_SUCCESS);
    }
    else
    {
        wait(NULL);
        printf("%d\n", *var);
        munmap(var, sizeof(*var));
    }
    return 0;
}