#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *start_routine(void *p)
{
    printf("HELLO WORLD\n");
    pthread_exit(0);
}
int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, start_routine, NULL);
    pthread_join(thread, NULL);
    return 0;
}