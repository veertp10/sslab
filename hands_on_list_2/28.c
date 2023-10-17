/*
============================================================================
Name : 28.c
Author : Veerendragouda.T.Patil
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    /* int msgqid;
    key_t key;

    Generate a unique key for the message queue (use the same key as the sender)
    if ((key = ftok(".", 'q')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open the message queue
    if ((msgqid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Obtain the current attributes of the message queue*/

    struct msqid_ds queue_info;
    if (msgctl(2, IPC_STAT, &queue_info) == -1) {
        perror("msgctl (IPC_STAT)");
        exit(EXIT_FAILURE);
    }

    // Modify the permissions (set them to 0644 as an example)
    queue_info.msg_perm.mode = 0644;

    // Update the message queue's attributes with the new permissions
    if (msgctl(2, IPC_SET, &queue_info) == -1) {
        perror("msgctl (IPC_SET)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue permissions updated successfully.\n");

    return 0;
}

