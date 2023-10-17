/*
============================================================================
Name : 25.c
Author : Veerendragouda.T.Patil
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
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

    printf("Message Queue Key: %d\n", key);1644563081

    printf("Message Queue ID: %d\n", msgqid);

    struct msqid_ds queue_info;

    // Get information about the message queue
    if (msgctl(msgqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // Access permission
    printf("Access Permission (octal): %#o\n", queue_info.msg_perm.mode);

    // UID and GID of the owner
    printf("Owner UID: %d\n", queue_info.msg_perm.uid);
    printf("Owner GID: %d\n", queue_info.msg_perm.gid);

    // Time of last message sent and received
    printf("Time of Last Message Sent: %s", ctime(&queue_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&queue_info.msg_rtime));

    // Time of last change in the message queue
    printf("Time of Last Change: %s", ctime(&queue_info.msg_ctime));

    // Size of the queue in bytes
    printf("Size of Queue (bytes): %lu\n", queue_info.msg_qbytes);

    // Number of messages in the queue
    printf("Number of Messages in Queue: %ld\n", queue_info.msg_qnum);

    // Maximum number of bytes allowed in the queue
    printf("Maximum Number of Bytes Allowed: %lu\n", queue_info.msg_qbytes);

    // PID of the last process that called msgsnd and msgrcv
    printf("PID of Last msgsnd: %d\n", queue_info.msg_lspid);
    printf("PID of Last msgrcv: %d\n", queue_info.msg_lrpid);

    return 0;
}

