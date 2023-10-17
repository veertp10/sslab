/*
============================================================================
Name : 14.c
Author : Veerendragouda.T.Patil
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
int i, j, fd[2];
char buf[80];
i = pipe(fd);
printf("i=%d\n", i);
j = write(fd[1], "Hello\n", 7);
read(fd[0], buf, j);
printf("From pipe: %s\n", buf);
}
