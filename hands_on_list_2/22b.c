/*
============================================================================
Name : 22.c
Author : Veerendragouda.T.Patil
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>

int main() {
char buff[80];
int fd;
fd = open("myfifo", O_WRONLY);
printf("Enter the text:");
scanf(" %[^\n]", buff);
write(fd, buff, sizeof(buff));
}
