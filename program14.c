#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
  if(argc!=2)
  {
    printf("Run it again");
    exit(1);
  }
  char *fname=argv[1];
  struct stat file_det;
  if(stat(fname,&file_det)==-1)
  {
    printf("There is an error while getting file information");
    exit(2);
  }
  if(S_ISREG(file_det.st_mode))
  {
    printf("\nRegular file");
  }
  else if(S_ISDIR(file_det.st_mode))
  {
    printf("\nDirectory");
  }
  else if(S_ISLNK(file_det.st_mode))
  {
    printf("\nSymbolic Link");
  }
  else if(S_ISBLK(file_det.st_mode))
  {
     printf("\nBlock device");
  }
  else if(S_ISCHR(file_det.st_mode))
  {
     printf("\nCharacter Device");
  }
  else if(S_ISFIFO(file_det.st_mode))
  {
     printf("\nFIFO file");
  }
  else if(S_ISSOCK(file_det.st_mode))
  {
     printf("\nSocket");
  }
  else
  {
    printf("Can't tell about this try again");
  }
  return 0;
}
