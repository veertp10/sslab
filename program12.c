#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
  int fd=open(argv[1],O_RDONLY);
  if(fd==-1)
  {
    printf("There is an error in opening the file");
    exit(1);
  }
  int flg=fcntl(fd,F_GETFL);
  int mod=flg & O_ACCMODE;
  if(mod==O_RDONLY)
  {
     printf("Read Only");
  }
  else if(mod==O_WRONLY)
  {
    printf("Write Only");
  }
  else if(mod==O_RDWR)
  {
    printf("Read and write both");
  }
  return 0;
}
