/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
create the record file to store records of faculty,student,course.
*/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
struct record{
int faculty;
int student;
int course;
};

void main(){
struct record my_record;
int fd,writeBytes;
fd=open("/home/veerendra/sslab/mine/records/record_file",O_CREAT | O_RDWR,0777);


if(fd==-1){
perror("Cannot Open File");
exit(1);
}
//Set credentials
my_record.faculty=0;
my_record.student=0;
my_record.course=0;
writeBytes=write(fd,&my_record,sizeof(my_record));
if(writeBytes<=0){
perror("Cannot write into file");
exit(1);
}
close(fd);
}
