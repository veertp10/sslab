#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
  if(argc!=4)
  {
    printf("Run it again");
    exit(1);
  }
  char info[10]="1234567890";
  int fd1;
  fd1=open(argv[1],O_WRONLY|O_APPEND);
  if(fd1==-1)
  {
    printf("Error in opening the file");
    exit(2);
  }
  //using dup
  int dp1=dup(fd1);
  if(dp1==-1)
  {
    printf("There is an error in duplicating file descriptor");
    exit(3);
  }
  write(dp1,info,10);
  int fd2=open(argv[2],O_WRONLY|O_APPEND);
  if(fd2==-1)
  { 
     printf("There is an error in opening the file");
    exit(2);
  }
  int dp2=dup2(fd2,6);
  if(dp2==-1)
  {
    printf("There is an error in duplicating the file descriptor");
    exit(3);
  }
  write(dp2,info,10);
  int fd3=open(argv[3],O_WRONLY|O_APPEND);
  if(fd3==-1)
  {  
     printf("There is an error in opening the file");
    exit(2);
  }
  int dp3=fcntl(fd3,F_DUPFD);
  if(dp3==-1)
  {
    printf("There is an error in duplicating the file descriptor");
    exit(3);
  }
  write(dp3,info,10);
  sleep(60);
  close(fd1);
  close(fd2);
  close(fd3);
}
