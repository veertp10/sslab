#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
struct
{
  int train_no;
  int ticket_no;
}db[3];
int main()
{
  int fd=open("traininfo.txt",O_RDWR);
  for(int i=0;i<3;i++)
  {
    db[i].train_no=i+1;
    db[i].ticket_no=0;
  }
  write(fd, db,sizeof(db));
  close(fd);
}
