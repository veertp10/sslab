#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
struct 
{
 int ticket_no;
}db;
int main()
{
  db.ticket_no=10;
  int fd=open("database.txt",O_CREAT|O_RDWR,0644);
  int a=write(fd,&db,sizeof(db));
  if(a==-1)
  {
    printf("write unsuccessful");
    return 0;
  }
  close(fd);
  fd=open("database.txt",O_RDONLY);
  read(fd,&db,sizeof(db));
  printf("Ticket no.%d\n",db.ticket_no);
  close(fd);
}
