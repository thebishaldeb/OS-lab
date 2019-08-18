#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <utmp.h>
#define BUF_SIZE 100

int main()
{
	char buf[BUF_SIZE];
	int count = 1;
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
		sprintf(buf, "Under GrandChild\n\tRoll No - CSB17076\n");
		write(1, buf, strlen(buf));
	}
	else if (child > 0 && grandChild > 0)
	{
		sprintf(buf, "Under Parent,\n\tPID is %d\n\tChild PID & PPID are %d & %d\n\tGrandChild PID and PPID are %d & %d\n", getpid(), child, getpid(), grandChild, child);
		write(1, buf, strlen(buf));
	}
	if (child == 0)
	{
		count++;
		if (grandChild == 0)
		{
			count++;
			printf("Total process Count: %d\n", count);
		}
	}
	exit(0);
}
