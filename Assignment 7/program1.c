#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>

#define KEY 0x1111

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

int main()
{
    char s[100];
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1, 0666 | IPC_CREAT);
    int *data = (int *)shmat(shmid, 0, 0);
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    if (id < 0)
    {
        perror("semget");
        exit(11);
    }
    union semun u;
    u.val = 1;
    if (semctl(id, 0, SETVAL, u) < 0)
    {
        perror("semctl");
        exit(0);
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(0);
    }
    else if (pid == 0)
    {
        int l = *data;
        printf("No of reads: %d\n", l);
        sleep(2);
        for (int i = 0; i < l; ++i)
        {
            if (semop(id, &p, 1) < 0)
            {
                perror("semop p");
                exit(0);
            }
            FILE *fp = fopen("demo.txt", "r");
            fgets(s, 100, fp);
            printf("%d - From pt 2: ", i + 1);
            puts(s);
            fflush(stdout);
            if (semop(id, &v, 1) < 0)
            {
                perror("semop v");
                exit(0);
            }
            fclose(fp);
            sleep(2);
        }
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }
    else
    {
        srand(time(0));
        int ran = rand() % 15;
        *data = ran;
        int l = *data;
        sleep(1);
        for (int i = 0; i < l; ++i)
        {
            if (semop(id, &p, 1) < 0)
            {
                perror("semop p");
                exit(0);
            }
            FILE *fp = fopen("demo.txt", "r");
            fgets(s, 100, fp);
            printf("%d - From pt 1: ", i + 1);
            puts(s);
            fflush(stdout);
            if (semop(id, &v, 1) < 0)
            {
                perror("semop v");
                exit(0);
            }
            fclose(fp);
            sleep(2);
        }
        shmdt(data);
    }
}
