#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/utsname.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Arguments error\n");
        printf("Enter: %s <executable file>\n", argv[0]);
        exit(1);
    }
    char buf[BUF_SIZE];
    pid_t child, grandChild;
    int stat;
    write(1, buf, strlen(buf));
    child = fork();
    if (child < 0)
    {
        sprintf(buf, "Fork error\n");
        write(1, buf, strlen(buf));
        exit(1);
    }
    if (child == 0)
    {
        execv(argv[1], NULL);
        printf("\n\n\n");
    	printf("%s\n", argv[0]);
    }
    wait(&stat);
    if (WIFEXITED(stat))
        printf("child has exited with exit code %d\n", WEXITSTATUS(stat));
    else
        printf("child has terminated abnormally\n");
    exit(0);
}
