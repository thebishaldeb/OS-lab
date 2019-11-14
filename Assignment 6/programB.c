#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>

int main()
{

    pid_t child;
    struct timeval before, after;
    gettimeofday(&before, NULL);
    child = fork();
    if (child < 0)
    {
        perror("Fork error.");
    }
    if (child == 0)
    {
        printf("This is under the child process\n");
        int i, j, k, l, m;
        for (i = 0; i < 10000; i++)
            for (j = 0; j < 100000; j++)
                ;
        FILE *fp;
        fp = fopen("demo2.txt", "w");
        fprintf(fp, "Submission time of child process: %ld seconds\n", before.tv_sec);
        gettimeofday(&after, NULL);
        fprintf(fp, "Termination time of child process: %ld seconds\n", after.tv_sec);
        printf("Child Exiting...\n");
        exit(0);
    }
    else
    {
        printf("This is under the parent process\n");
        wait(NULL);
        printf("Parent Exiting...\n");
    }
    exit(0);
}