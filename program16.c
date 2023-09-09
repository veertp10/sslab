#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char* argv[])
{
  struct flock implock;
  int fd;
  fd=open(argv[1],O_RDWR);
  implock.l_whence=SEEK_SET;
  implock.l_start=0;
  implock.l_len=0;
  implock.l_pid=getpid();
  int choice;
  printf("Enter the choice which lock you want 1 for Read lock and 2 for write lock\n");
  scanf("%d",&choice);
  fflush(stdin);
  switch(choice)
  {
    case 1:
        implock.l_type=F_RDLCK;
        printf("Before entering into critical section");
        fcntl(fd,F_SETLKW,&implock);
        printf("Inside the critical section");
        printf("Enter to unlock");
        getchar();
        printf("File unlocked");
        implock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&implock);
        break;
     case 2:
         implock.l_type=F_WRLCK;
         printf("Before entering into critical section");
         fcntl(fd,F_SETLKW,&implock);
         printf("Inside the critical section");
         printf("\nEnter to unlock");
         getchar();
         printf("File unlocked");
         implock.l_type=F_UNLCK;
         fcntl(fd,F_SETLKW,&implock);
         break;
     default:
         printf("Enter proper choice");
  }  
}
