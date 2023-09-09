#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
  if(argc!=2)
  { 
    printf("Run it again");
    exit(1);
  }
  char first[]="1234567890";
  char second[]="1234567890";
  int fd;
  fd=open(argv[1],O_RDWR|O_CREAT);
  if(fd==-1)
  {
    printf("File can't be open");
    exit(2);
  }
  int wr1=write(fd,first,10);
  if(wr1==-1)
  {
    printf("Write is unsuccessfull");
    exit(3);
  }
  int offset=lseek(fd,10,SEEK_CUR);
  printf("The return value of the lseek %d",offset);
  int wr2=write(fd,second,10);
  if(wr2==-1)
  {
    printf("Write unsuccessful");
    exit(3);
  }
  int c=close(fd);
 if(c==0)
 {
  printf("\nClose successful");
 }
 else
 {
   printf("\nClose unsuccessful");
 }
 return 0;
}
