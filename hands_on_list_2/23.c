/*
============================================================================
Name : 23.c
Author : Veerendragouda.T.Patil
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
============================================================================
*/
#include<unistd.h>
#include<stdio.h>

int main() {
long pipe_buf, open_max;
pipe_buf = pathconf(".",_PC_PIPE_BUF);
open_max = sysconf(_SC_OPEN_MAX);
printf("maximum number of files can be opened within a process:%ld\n size of a pipe (circular buffer):%ld\n",open_max,pipe_buf);
}
