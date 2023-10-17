/*
============================================================================
Name : 27.c
Author : Veerendragouda.T.Patil
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msgbuf {
    long mtype;
    char mtext[1000];
};

int main() {
    int msgqid;
    key_t key;
    struct msgbuf message;

    // Generate a unique key for the message queue (use the same key as the sender)
    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open the message queue
    if ((msgqid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Receive a message from the queue (blocks until a message is available)
    //IPC_NOWAIT in place of zero
    if (msgrcv(msgqid, &message, sizeof(message.mtext), 0, IPC_NOWAIT ) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received Message: %s\n", message.mtext);

    return 0;
}

