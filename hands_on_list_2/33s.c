/*
============================================================================
Name : 33.c
Author : Veerendragouda.T.Patil
Description : Write a program to communicate between two machines using socket.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include<time.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
struct sockaddr_in serv, cli;
int sd, nsd;
int sz;
char buf[80];

// sd = Socket Descriptor
sd = socket(AF_UNIX, SOCK_STREAM, 0);
serv.sin_family = AF_UNIX;
// Specify destination address of socket
// INADDR_ANY = Automatically assign IP address (of current machine)
serv.sin_addr.s_addr = INADDR_ANY;
// Meaning of htons() will be explained later
serv.sin_port = htons(3558);
// sd has become the server now
bind(sd, (void*) (&serv), sizeof(serv));
listen(sd, 5); // 5 = size of wait queue for connections
sz = sizeof(cli);
// Accept connection from client and put its details in cli
// Server will wait at this line till a client connects with proper
//IP address and port number
// nsd = New Socket Descriptor
nsd = accept(sd, (void*) (&cli), &sz);
// Read data sent by cli (nsd) and store it in buf
read(nsd, buf, sizeof(buf));
printf("Message from client: %s\n", buf);
write(nsd, "ACK from Server\n", 17);
}
