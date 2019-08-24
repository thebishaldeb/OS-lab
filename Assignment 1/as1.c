#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	if(child == 0){
		grandChild = fork();
		if (grandChild < 0)
		{
			sprintf(buf, "Fork error\n");
			write(1, buf, strlen(buf));
			exit(1);
		}
		else if (grandChild == 0)
		{
			int PPIDg = getppid(), PIDg = getpid();
			sprintf(buf, "Under GrandChild\n\tRoll No - CSB17076. PID: %d. PPID: %d\n",PIDg, PPIDg);
			write(1, buf, strlen(buf));
			FILE *fp = fopen("ppidG.txt", "w");
			fprintf(fp,"%d %d ", PIDg , PPIDg);
			fclose(fp);
		} else {
			sprintf(buf, "Under Child\n\tPID is %d and PPID is %d\n", getpid(), getppid());
			write(1, buf, strlen(buf));
		}
	}
	wait(NULL);
	
	if (child > 0)
	{
		int PIDg, PPIDg;
		FILE *fp = fopen("ppidG.txt", "r");
		fscanf(fp,"%d %d ",&PIDg,&PPIDg);
		fclose(fp);
		sprintf(buf, "Under Parent,\n\tPID is %d\n\tChild PID & PPID are %d & %d\n\tGrandChild PID and PPID are %d & %d\n", getpid(), child, getpid(), PIDg, PPIDg);
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
