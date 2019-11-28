#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handlerfunc(int sig)
{
    int pfds[2];
    int i, a, b, c, N, pi[1], ppi[1];
    printf("Enter number of terms to display: ");
    scanf("%d", &N);
    int ca[N], pa[N];
    pipe(pfds);
    if (!fork())
    {
        printf("CHILD(PID: %d): from child\n", getpid());
        pi[0] = getpid();
        write(pfds[1], pi, sizeof(int));
        a = 0, b = 1;
        ca[0] = a;
        ca[1] = b;
        for (i = 2; i < N; i++)
        {
            c = a + b;
            a = b;
            b = c;
            ca[i] = c;
        }
        write(pfds[1], ca, N * sizeof(int));
        printf("CHILD: exiting\n");
        pi[0] = sig;
        write(pfds[1], pi, sizeof(int));
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("PARENT: reading from pipe\n");
        read(pfds[0], ppi, sizeof(int));
        printf("CHILD(PID: %d) :writing from parent\n", ppi[0]);
        read(pfds[0], pa, N * sizeof(int));
        for (i = 0; i < N; i++)
            printf("%d\n", pa[i]);
        read(pfds[0], ppi, sizeof(int));
        printf("signal id for which handler is generated (CTRL+C)= %d\n", ppi[0]);
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
