#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utmp.h>
#include <errno.h>
#include <signal.h>

#define BUF_SIZE 100

int main()
{
    printf("\nExample program to be killed by another program!\n");
    pid_t PID = getpid();
    printf("\nPID: %d\n", PID);
    FILE *fp = fopen("ppidG.txt", "w");
    fprintf(fp, "%d ", PID);
    fclose(fp);
    while (1)
    {
    }
    exit(0);
}
