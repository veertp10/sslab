#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<limits.h>
int main(int argc,char *argv[])
{
  if(argc!=2)
  {
    printf("Please enter the file name that you want to read");
    exit(1);
  }
  int fd=open(argv[1],O_RDONLY);
  if(fd==-1)
  {
    printf("File not opened Try it again");
    exit(2);
  }
  //we are assuming the maximum size of a line 1024
  char buffer[1024];
  char ans[1024];
  while(1)
 {
   int r1=read(fd,buffer,1024);
   if(r1==0)
   break;
   if(r1==-1)
   {
     printf("Error in opening the file");
     exit(3);
   }
 int k=0;
  for(int i=0;i<r1;i++)
  {
     if(buffer[i]=='\n')
     {
        ans[k]='\0';
        printf("%s\n",ans);
        k=0;
     }
    else
    {
      ans[k++]=buffer[i];
    }
  }
 }
 int c1=close(fd);
 if(c1==-1)
 {
   printf("File not closed successfully");
 }
 else
 { 
  printf("File closed successfully");
 }
 return 0;
}
