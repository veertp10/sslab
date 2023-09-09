 #include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
    int cpid=fork();
    if(cpid==-1)
    {
        printf("\nCan't create the child process");
        exit(1);
    }   
    else if(cpid==0)
    {
        printf("\nI am chid and now my parent process id is %d",getppid());
        sleep(8);
        printf("\nI am child and now my parent process id is %d",getppid());
    }
    else
    {
        printf("im parent my id id:%d\n",getpid());   
        sleep(4);
    }
}
