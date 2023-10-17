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
#include <sys/select.h>


int main() {
char buff[80];
int fd;
fd_set rfds;
struct timeval tv;
tv.tv_sec = 10;
fd = open("myfifo", O_RDONLY);
FD_ZERO(&rfds);
FD_SET(fd, &rfds);
if (!select(fd + 1, &rfds, NULL, NULL, &tv))
printf("No data is available for reading yet\n");
else {
printf("Data is available now\n");
read(fd, buff, sizeof(buff));
printf("Data from FIFO: %s\n", buff);
}
// Do other tasks
}
