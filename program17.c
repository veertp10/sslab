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
 struct flock implock;
 implock.l_type=F_WRLCK;
 int fd=open("database.txt",O_RDWR);
 printf("Before entering into critical section\n");
 fcntl(fd,F_SETLKW,&implock);
 printf("\nInside the critical section");
 read(fd,&db,sizeof(db));
 printf("\nCurrent ticket number %d",db.ticket_no);
 db.ticket_no++;
 lseek(fd,0,SEEK_SET);
 write(fd,&db,sizeof(db));
 printf("\nPress enter to unlock");
 getchar();
 implock.l_type=F_UNLCK;
 fcntl(fd,F_SETLK,&implock);
 printf("\nOutside of the critical section");
 close(fd);
}
