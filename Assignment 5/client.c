/*Assignment 5A
-to demonstrate the IPC mechanism using Message Queue functionality
*/
/*  IMPORTANT TERMS:
-linked list of messages-> stored within the kernel
-Message Queue Identifier
-messages are fetched not in a FIFO order but based on their type field
-processes must share a common key->gaining access to the queue in the first place
*/

//this is the client file->it will receive a message from the server file

//import statements
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

//message queue node structure
struct message_queue
{
    long type;
    char message[200];
} a;

int main()
{
    key_t key = ftok("IPCMQ", 17);
    //connect to the message queue
    int queue_id = msgget(key, 0666 | IPC_CREAT);
    //recv the message and store and display it
    msgrcv(queue_id, &a, sizeof(a), 1, 0);
    printf("\nMessage received: %s\n", a.message);

    //destroy the message queue
    msgctl(queue_id, IPC_RMID, NULL);
    return 0;
}

/*              Functions:
--msgget(): -create a message queue/connect to already created message queue
            -parameters--> queue key+ flag
--msgsnd(): -write into the message queue-->add a node to the message queue linked list            
--msgrcv(): -read from the message queue
--msgctl(): -control operations on the message queue
*/