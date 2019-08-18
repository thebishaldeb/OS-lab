#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/utsname.h>

#define BUF_SIZE 100

void loggedIn()
{
    struct utmp *n;
    setutent();
    n = getutent();
    printf("Under GrandChild,\n\tCurrent logged-in users:");
    while (n)
    {
        if (n->ut_type == USER_PROCESS)
        {
            printf("\n\t\t%s", n->ut_user);
        }
        n = getutent();
    }
    printf("\n");
}

int main()
{
    char buf[BUF_SIZE];
    pid_t child, grandChild;
    write(1, buf, strlen(buf));
    child = fork();
    if (child < 0)
    {

        sprintf(buf, "Fork error\n");
        write(1, buf, strlen(buf));
        exit(1);
    }
    grandChild = fork();
    if (grandChild < 0)
    {
        sprintf(buf, "Fork error\n");
        write(1, buf, strlen(buf));
        exit(1);
    }
    if (child == 0 && grandChild > 0)
    {
        sprintf(buf, "Under Child\n\tPID is %d and PPID is %d\n", getpid(), getppid());
        write(1, buf, strlen(buf));
    }
    else if (grandChild == 0 && child == 0)
    {
        loggedIn();
    }
    else if (child > 0 && grandChild > 0)
    {
        sprintf(buf, "Under Parent,\n\tPID is %d\n\tChild PID & PPID are %d & %d\n\tGrandChild PID and PPID are %d & %d\n", getpid(), child, getpid(), grandChild, child);
        write(1, buf, strlen(buf));
    }
    wait(NULL);
    exit(0);
}
