/*
============================================================================
Name : 20.c
Author : Veerendragouda.T.Patil
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
============================================================================
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>

int main() {
char buff[2];
int fd;
fd = open("myfifo", O_WRONLY);
printf("Enter the text:");
scanf(" %[^\n]", buff);
write(fd, buff, sizeof(buff));
}
