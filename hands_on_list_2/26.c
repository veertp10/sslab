/*
============================================================================
Name : 26.c
Author : Veerendragouda.T.Patil
Description : Write a program to send messages to the message queue. Check $ipcs -q
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

// Define a structure for the message
struct msgbuf {
    long mtype; // Message type
    char mtext[256]; // Message text (adjust the size as needed)
};

int main() {
    int msgqid;
    key_t key;
    struct msgbuf message;
    
    // Generate a unique key for the message queue (you can use ftok or any method you prefer)
    key = ftok(".", 'q');
    
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Open or create the message queue
    msgqid = msgget(key, IPC_CREAT | 0666);
    
    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue ID: %d\n", msgqid);

    // Prompt the user for message type and text
    printf("Enter message type (a positive integer): ");
    scanf("%ld", &message.mtype);

    printf("Enter message text: ");
    scanf(" %[^\n]", message.mtext);

    // Send the message to the queue
    if (msgsnd(msgqid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the queue.\n");

    // Check the status of the message queue using ipcs -q
    printf("Use 'ipcs -q' to check the message queue's status.\n");

    return 0;
}

