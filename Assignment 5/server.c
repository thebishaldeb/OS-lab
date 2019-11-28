/*Assignment 5A
-to demonstrate the IPC mechanism using Message Queue functionality
*/
/*  IMPORTANT TERMS:
-linked list of messages-> stored within the kernel
-Message Queue Identifier
-messages are fetched in a FIFO order but based on their type field
-processes must share a common key->gaining access to the queue in the first place
*/

//this is the server file--> it will send a message to the client file
//import statements
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
//message queue node structure
struct message_queue
{
    long type;
    char message[200];
} a;

int main(int argc, const char *argv[])
{
    key_t key = ftok("IPCMQ", 17);
    //accept the input string as cmd line argument
    if (argc < 2)
    {
        printf("\nInsufficient arguments!\n");
        exit(0);
    }
    else
    {
        strcpy(a.message, argv[1]);
    }
    a.type = 1;
    //create a message queue
    int queue_id = msgget(key, 0666 | IPC_CREAT);
    //write to the message queue
    if (msgsnd(queue_id, &a, sizeof(a), 0) == 0)
    {
        printf("\nMessage written successfully\n");
    }
    return 0;
}