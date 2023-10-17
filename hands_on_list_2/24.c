/*
============================================================================
Name : 24.c
Author : Veerendragouda.T.Patil
Description : Write a program to create a message queue and print the key and message queue id.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgqid;

    // Generate a unique key for the message queue
    if ((key = ftok(".", 'b')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue with the specified key
    if ((msgqid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgqid);

    return 0;
}
/*
int main() {
// 'a' = ASCII value of "a" given as proj_id and "." will be string
//used to create key
key_t key;
int msgid;
key = ftok(".", 'a');
msgid = msgget(key, IPC_CREAT|IPC_EXCL|0744);
// %0x for Hexadecimal value
printf("key=0x%0x\t msgid=%d\n", key, msgid);
}
*/
