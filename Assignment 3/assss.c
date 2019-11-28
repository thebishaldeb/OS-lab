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

void sigint_handler(int sig)
{
    printf("\n\nSignal received!\n");
    char buf[BUF_SIZE];
    pid_t child;
    printf("\nCreating Fork...\n\n");
    child = fork();
    if (child < 0)
    {
        sprintf(buf, "Fork error\n");
        write(1, buf, strlen(buf));
        exit(1);
    }
    if (child == 0)
    {
        int num, i;
        printf("Under Child\n\tPID is %d\nPlease enter a number of terms for Fibonacci series: ", getpid());
        scanf("%d", &num);
        int Fib[num];
        Fib[0] = 0;
        Fib[1] = 1;
        for (i = 2; i < num; i++)
        {
            Fib[i] = Fib[i - 1] + Fib[i - 2];
        }

        for (i = 0; i < num; i++)
        {
            printf("%d\n", Fib[i]);
        }
    }
    else
    {
        wait(NULL);
        sprintf(buf, "Under Parent\n\tPID is %d and PPID is %d\n", getpid(), getppid());
        write(1, buf, strlen(buf));
    }
    exit(0);
}

int main()
{
    printf("\nPress ^C to send the signal!\n\n");
    while (1)
    {
        if (signal(SIGINT, sigint_handler) == SIG_ERR)
        {
            perror("Signal");
            exit(1);
        }
    }
    exit(0);
}
