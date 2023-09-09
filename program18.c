#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
struct 
{
 int train_no;
 int ticket_no;
}db;
int main()
{ 
 int  fd=open("traininfo.txt",O_RDWR);
  int choice;
  printf("Enter your choice you want to view train how many tickets are booked or you want to book a ticket\n");
  printf("1->view\n");
  printf("2->Book\n");
  scanf("%d",&choice);
  fflush(stdin);
  int trno;
  struct flock lock;
  switch(choice)
  {
     case 1:
          printf("\nEnter train no.");
          scanf("%d",&trno);
          lock.l_type=F_RDLCK;
          lock.l_whence=SEEK_SET;
          lock.l_start=(trno-1)*sizeof(db);
          lock.l_len=sizeof(db);
          lock.l_pid=getpid();
          lseek(fd,(trno-1)*sizeof(db),SEEK_SET);
          read(fd,&db,sizeof(db));
          printf("\nBefore entering into critical section\n");          
          fcntl(fd,F_SETLKW,&lock);
          printf("\nTicket count is %d",db.ticket_no);
          printf("\nTo exit press enter");
          getchar();
          getchar();
          lock.l_type=F_UNLCK;
          fcntl(fd,F_SETLK,&lock);
          break;
     case 2:
         printf("\nEnter train no");
         scanf("%d",&trno);
         lock.l_type=F_WRLCK;
         lock.l_whence=SEEK_SET;
         lock.l_start=(trno-1)*sizeof(db);
         lock.l_len=sizeof(db);
         lock.l_pid=getpid();
         lseek(fd,(trno-1)*sizeof(db),SEEK_SET);
         read(fd,&db,sizeof(db));
         printf("Before enetring critical section\n");
         fcntl(fd,F_SETLKW,&lock);
         printf("The current ticket no %d",db.ticket_no);
         db.ticket_no++;
         lseek(fd,-1*sizeof(db),SEEK_CUR);
         write(fd,&db,sizeof(db));
         printf("\nEnter to book the ticket");
         getchar();
         getchar();
         lock.l_type=F_UNLCK;
         fcntl(fd,F_SETLK,&lock);
         printf("\nNew ticket number %d",db.ticket_no);
         break;
     default:
        printf("Wrong choice");
  }
}
