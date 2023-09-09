#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
  fd_set fds;
  struct timeval var;
  int value;
  FD_ZERO(&fds);
  FD_SET(0,&fds);
  var.tv_sec=10;
  var.tv_usec=0;
  int res=select(1,&fds,NULL,NULL,&var);
  if(res==-1)
  {
     printf("There is an error");
     exit(1);
  }
  else if(res==0)
  {
    printf("No data available within 10 seconds");
  }
  else
  {
    printf("User has inputed the data within 10 seconds");
  }
  return 0;
}
