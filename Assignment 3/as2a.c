//part 1 3b
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int fd;
    char *FIFO = "/tmp/FIFO";
    mknod(FIFO, S_IFIFO | 0666, 0);
    char arr[100];
    while (1)
    {
        fd = open(FIFO, O_WRONLY);
        printf("\n  Message from Programe 1:");
        fgets(arr, 80, stdin);
        write(fd, arr, strlen(arr) + 1);
        close(fd);

        memset(arr, 0, sizeof(arr));

        fd = open(FIFO, O_RDONLY);
        read(fd, arr, sizeof(arr));
        printf("\nMessage from Programe2:%s\n", arr);
        close(fd);
    }
    return 0;
}

