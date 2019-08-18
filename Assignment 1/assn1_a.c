#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<utmp.h>

int main() {
  pid_t a, b;
  
  a = fork();
  if(a < 0) {
    printf("Child Process could not be created");
    exit(1);
  } else if(a  == 0) {
    printf("Child says, PID: %d\n", getpid());
    printf("Child says, PPID: %d\n", getppid());
    b = fork();
    if(b < 0) {
    printf("Child Process could not be created");
    exit(1);
    } else if(b  == 0) {
      printf("Grandchild says, roll no: CSB17011\n");
      exit(0);
    } else {
      exit(0);
    } 
  } else {
    printf("From parent, my PID: %d\n", getpid());
    printf("From parent, my PPID: %d\n", getppid());
    printf("From parent, PID of child: %d\n", a);
    printf("From parent, PPID of child: %d\n", getpid());
    printf("From parent, PPID of grandchild: %d\n", a);
    exit(0);
  }
  return 0;
}