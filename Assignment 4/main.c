#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    //declaring the structure of the flock and setting up its members:
    struct flock f1;
    f1.l_type = F_WRLCK;
    f1.l_whence = SEEK_SET;
    f1.l_start = 0;
    f1.l_len = 0;
    f1.l_pid = getpid();
    //opening the file
    if ((fd = open("demo.txt", O_RDWR)) == -1)
    {
        perror("\nError in opening the file!");
        exit(1);
    }
    //check and set the lock
    if (fcntl(fd, F_SETLK, &f1) == -1)
    {
        perror("\nerror in fcntl-lock");
        exit(1);
    }
    //read the file
    char read_string[200];
    int last_index = read(fd, read_string, sizeof(read_string));
    read_string[last_index] = '\0';
    puts(read_string);
    //release the lock
    f1.l_type = F_UNLCK;
    printf("\nPress <RETURN> to unlock the file!\n");
    getchar();
    if (fcntl(fd, F_SETLK, &f1) == -1)
    {
        perror("\nerror in fcntl-release!");
        exit(1);
    }
    printf("\nUnlocked.\n");
    close(fd);
    return 0;
}