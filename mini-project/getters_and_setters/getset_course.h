/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
course get_course_details(int course_no):To get the details of the course.
set_course_details(int course_no, struct course *my_course):To set detail values of the course.
remove_offered_course(int course_no):remove the offered course.
save_course(struct course *my_course):save the course offered by the user.
*/


#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct course get_course_details(int course_no){
int rBytes,wBytes, fd, offset;
struct course my_course;
//check validity of course_no
if(is_validId(2,course_no)){
//valid

fd=open("./records/course_file",O_RDONLY);
if(fd==-1){
perror("Cannot Open File");
return (struct course){-1,-1,"NULL",0,0,0};
}
offset=lseek(fd,course_no*sizeof(struct course),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in course File");
return (struct course){-1,-1,"NULL",0,0,0};
}

/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, course_no*sizeof(struct course), sizeof(struct course), getpid()};
int lockingStatus = fcntl(fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on Account record!");
return (struct course){-1,-1,"NULL",0,0,0};
}
/*...........*/
rBytes=read(fd,&my_course,sizeof(my_course));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/

if(rBytes<=0){
perror("Cannot read the file");
return (struct course){-1,-1,"NULL",0,0,0};
}
close(fd);
}
else{
printf("Record Not Exists\n");
return (struct course){-1,-1,"NULL",0,0,0};
}
//success...
return my_course;
}

/* Setter Program */

bool set_course_details(int course_no, struct course *my_course){
int rBytes,wBytes, fd, offset;
//check validity of faculty-Id
if(is_validId(2,course_no)){
//valid
my_course->course_id=course_no;
fd=open("./records/course_file",O_WRONLY);
if(fd==-1){
perror("Cannot Open File");
return 0;
}
offset=lseek(fd,course_no*sizeof(struct course),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in course File");
return 0;
}
/*Setting Lock*/
struct flock lock = {F_WRLCK, SEEK_SET, course_no*sizeof(struct course), sizeof(struct course), getpid()};
int lockingStatus = fcntl(fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on Account record!");
return 0;
}
/*...........*/
wBytes=write(fd,&(*my_course),sizeof(*my_course));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/
if(wBytes<=0){
perror("Cannot write into the file");
return 0;
}
close(fd);
}
else{
printf("Record Not Exists\n");
return 0;
}

//success...
return 1;
}


bool remove_offered_course(int course_no){

struct course my_course;
my_course=get_course_details(course_no);
if(my_course.course_id==-1)
return 0;

my_course.course_status=0;
if(set_course_details(course_no,&my_course))
return 1;

return 0;
}


bool activate_course(int course_no){

struct course my_course;
my_course=get_course_details(course_no);
if(my_course.course_id==-1)
return 0;

my_course.course_status=1;//activate...
if(set_course_details(course_no,&my_course))
return 1;

return 0;
}

int save_course(struct course *my_course){
int course_no;
int rBytes,wBytes, fd, offset;
//set available course-no...
course_no=get_record_details(2);
if(course_no==-1) return -1;

my_course->course_id=course_no;

fd=open("./records/course_file",O_WRONLY | O_CREAT,0777);
if(fd==-1){
perror("Cannot Open File");
return -1;
}
offset=lseek(fd,course_no*sizeof(struct course),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in course File");
return -1;
}
/*Setting Lock: Mandatory*/
struct flock lock = {F_WRLCK, SEEK_SET, 0,0, getpid()};
int lockingStatus = fcntl(fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on course file!");
return 0;
}
/*...........*/
wBytes=write(fd,&(*my_course),sizeof(*my_course));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/
if(wBytes<=0){
perror("Cannot write into the file");
return -1;
}
close(fd);

//upadate available course-no...
if(!set_record_details(2,course_no+1)){
printf("Error while updating record file\n");
return -1;
}
//success...
return course_no;
}


