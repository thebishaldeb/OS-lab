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
    printf("\nSignal received: %d\n", sig);
    int PIDg;
    FILE *fp = fopen("ppidG.txt", "r");
    fscanf(fp, "%d ", &PIDg);
    fclose(fp);
    printf("\nPID of the process to be killed is %d\n", PIDg);
    kill(PIDg, sig);
    // char buf[BUF_SIZE];
    exit(0);
}

int main()
{
    printf("Press ^C to send the signal!\n");
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
