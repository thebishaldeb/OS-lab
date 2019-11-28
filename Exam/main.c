#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int checkPrime(int n)
{
    int i;
    for (i = 2; i <= n / 2; ++i)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void handlerfunc(int sig)
{
    int pipefds[2];
    int returnstatus;
    char writemessages[3][20] = {"Prime", "Not prime", "Thank You!"};
    char readmessage[20];
    returnstatus = pipe(pipefds);
    if (returnstatus == -1)
    {
        printf("Unable to create pipe\n");
        exit(1);
    }
    int pid = fork();
    if (pid == 0)
    {
        int N[1];
        printf("\nEnter number: ");
        scanf("%d", N);
        while (N[0] < 2)
        {
            printf("\nEnter again: ");
            scanf("%d", N);
        }
        printf("Child Process - Writing to pipe -  Number: %d\n", N[0]);
        write(pipefds[1], N, sizeof(int));
        sleep(1);
        read(pipefds[0], readmessage, sizeof(readmessage));
        printf("Child Process - Reading from pipe - Message: %s\n", readmessage);

        printf("Child Process - Writing to pipe -  Mesaage: %s\n", writemessages[2]);
        write(pipefds[1], writemessages[2], sizeof(writemessages[2]));
        exit(0);
    }
    else
    {
        int N[1];
        read(pipefds[0], N, sizeof(int));

        printf("Parent Process - Reading from pipe – Number: %d\n", N[0]);
        if (!checkPrime(N[0]))
        {
            printf("%d is not prime\n", N[0]);
            printf("Parent Process - Writing to pipe -  Mesaage: %s\n", writemessages[1]);
            write(pipefds[1], writemessages[1], sizeof(writemessages[1]));
        }
        else
        {
            printf("%d is prime\n", N[0]);
            printf("Parent Process - Writing to pipe -  Mesaage: %s\n", writemessages[0]);
            write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
        }
        sleep(1);
        read(pipefds[0], readmessage, sizeof(readmessage));
        printf("Parent Process - Reading from pipe – Message: %s\n", readmessage);
        exit(0);
    }
}

int main()
{
    signal(SIGINT, handlerfunc);
    printf("Press Ctrl+C\n");
    while (1)
    {
        sleep(1);
    }
    return 0;
}
