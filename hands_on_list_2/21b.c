/*
============================================================================
Name : 21.c
Author : Veerendragouda.T.Patil
Description : 21. Write two programs so that both can communicate by FIFO -Use two way communications.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>

int main() {
char buff1[80];
char buff2[80];
int fd1,fd2;
fd1 = open("myfifo1", O_RDONLY);
fd2 = open("myfifo2", O_WRONLY);
read(fd1, buff1, sizeof(buff1));
printf("The text from FIFO file: %s\n", buff1);
printf("Enter the text:");
scanf(" %[^\n]", buff2);

write(fd2, buff2, sizeof(buff2));


}
