/*
============================================================================
Name : 16.c
Author : Veerendragouda.T.Patil
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>





int main() {
char buff1[80];
char buff2[80];
int fd1[2];
pipe(fd1);
int fd2[2];
pipe(fd2);

if (!fork()) {
close(fd1[0]); // Close read-end of fd1 for child
close(fd2[1]); // Close write-end of fd2 for child
printf("Enter message to parent: ");
scanf(" %[^\n]", buff1);
write(fd1[1], buff1, sizeof(buff1));
read(fd2[0], buff2, sizeof(buff2));
printf("Message from parent: %s\n", buff2);
}
else {
close(fd1[1]); // Close read-end of fd1 for parent
close(fd2[0]); // Close read-end of fd2 for parent
// Child wrote into fd1 first, so read from fd1 first
read(fd1[0], buff1, sizeof(buff1));
printf("Message from child: %s\n", buff1);
printf("Enter message to child: ");
scanf(" %[^\n]", buff2);
write(fd2[1], buff2, sizeof(buff2));

}
}
