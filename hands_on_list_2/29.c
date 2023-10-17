/*
============================================================================
Name : 29.c
Author : Veerendragouda.T.Patil
Description : Write a program to remove the message queue.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    /* int msgqid;
    key_t key;

    // Generate a unique key for the message queue (use the same key as the sender)
    if ((key = ftok(".", 'q')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open the existing message queue
    if ((msgqid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }*/

    // Remove the message queue
    if (msgctl(2, IPC_RMID, NULL) == -1) {
        perror("msgctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

