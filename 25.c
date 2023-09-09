#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
    int cpid[3];
    for(int i=0;i<3;i++)
    {
        cpid[i]=fork();
        if(cpid[i]==0)
        {
            printf("\nThis is child %d and my process id is %d",i+1,getpid());
            exit(i);
        }
        else if(cpid[i]==-1)
        {
            printf("\nError in creating the file");
        }
    }
    int term_pid=waitpid(cpid[2],NULL,0);
    printf("\nWe want to terminate the %d and we have successfully terminated %d",cpid[2],term_pid);
}
