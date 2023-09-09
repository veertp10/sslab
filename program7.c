#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    printf("Run it again");
    exit(1);
  }
  char buffer;
  int first=open(argv[1],O_RDONLY);
  if(first==-1)
  {
    printf("Can't open this file");
    exit(2);
  }
  int second=open(argv[2],O_WRONLY|O_CREAT,0644);
  if(second==-1)
  {
    printf("Can't open this file");
    exit(3);
  }
  while(1)
  {
    int r1=read(first,&buffer,1);
    if(r1==-1)
    {
      printf("Error in reading the file");
      exit(4);
    }
    if(r1==0)
    {
      break;
    }
   int w2=write(second,&buffer,1);
   if(w2==-1)
   {
     printf("Can't write in this file");
     exit(5);
   }
  }
  int c1=close(first);
  if(c1==-1)
  {
    printf("Error in closing the file");
    exit(6);
  }
  int c2=close(second);
  if(c2==-1)
  {
    printf("Error in closing the file");
     exit(6);
  }
  printf("All operations performed successfully");
  return 0;
}
