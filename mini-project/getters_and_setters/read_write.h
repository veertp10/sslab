/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
read_msg(int cfd, struct message *msg):read the message from by the client.
write_msg(int cfd,int type, int action, char* body):write message to the client.
write_msg2(int cfd,int type, int action, char* body, int number):write message to the server.
*/


#include<stdbool.h>

bool read_msg(int cfd, struct message *msg){
int readBytes;
bzero(msg->body,sizeof(msg->body));
readBytes=read(cfd,&(*msg),sizeof(*msg));
if(readBytes<0)
return 0;

return 1;
}

bool write_msg(int cfd,int type, int action, char* body){
int writeBytes;
struct message msg;
msg.id=0;
msg.type=type;
msg.action=action;
strcpy(msg.body,body);
writeBytes=write(cfd,&msg,sizeof(msg));
if(writeBytes<0)
return 0;

return 1;
}

bool write_msg2(int cfd,int type, int action, char* body, int number){
int writeBytes;
struct message msg;
msg.id=0;
msg.type=type;
msg.action=action;
sprintf(msg.body,"%s->%d\n",body,number);
writeBytes=write(cfd,&msg,sizeof(msg));
if(writeBytes<0)
return 0;

return 1;
}



