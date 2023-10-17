/*
============================================================================
Name : 19.c
Author : Veerendragouda.T.Patil
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *fifoPath = "p"; // Name of the FIFO file

    // Create the FIFO file using the mknod system call
    if (mknod(fifoPath, S_IFIFO | 0666, 0) == -1) {
        perror("error while creating pipe:");
    } else {
        printf("FIFO file created successfully.\n");
    }

    return 0;
}

//mkfifo("myfifo", 0666);

