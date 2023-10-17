/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
get_faculty_details(int faculty_id):to get the desired faculty details if valid.
set_faculty_details(int faculty_id, struct faculty *my_faculty):set the faculty details.
save_faculty(struct faculty *my_faculty):save the faculty details given by admin.
*/


#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


struct faculty get_faculty_details(int faculty_id){
int rBytes,wBytes, fd, offset;
struct faculty my_faculty;
//check validity of faculty-id
if(is_validId(0,faculty_id)){
//valid
fd=open("./records/faculty_file",O_RDONLY);
if(fd==-1){
perror("Cannot Open File");
return (struct faculty){-1,"NULL","NULL","NULL",{-1,-1,-1,-1,-1},0};
}
offset=lseek(fd,faculty_id*sizeof(struct faculty),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in faculty File");
return (struct faculty){-1,"NULL","NULL","NULL",{-1,-1,-1,-1,-1},0};
}
/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, faculty_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
int lockingStatus = fcntl(fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining lock");
return (struct faculty){-1,"NULL","NULL","NULL",{-1,-1,-1,-1,-1},0};
}
/*...........*/
rBytes=read(fd,&my_faculty,sizeof(my_faculty));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/
if(rBytes<=0){
perror("Cannot read the file");
return (struct faculty){-1,"NULL","NULL","NULL",{-1,-1,-1,-1,-1},0};
}
close(fd);
}
else{
printf("Record Not Exists\n");
return (struct faculty){-1,"NULL","NULL","NULL",{-1,-1,-1,-1,-1},0};
}

//success...
return my_faculty;
}

/* Setter Program */

bool set_faculty_details(int faculty_id, struct faculty *my_faculty){
int rBytes,wBytes, fd, offset;
//check validity of faculty-Id
if(is_validId(0,faculty_id)){
//valid
my_faculty->fact_id=faculty_id;
fd=open("./records/faculty_file",O_WRONLY);
if(fd==-1){
perror("Cannot Open File");
return 0;
}
offset=lseek(fd,faculty_id*sizeof(struct faculty),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in faculty File");
return 0;
}
/*Setting Lock*/
struct flock lock = {F_WRLCK, SEEK_SET, faculty_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
int lockingStatus = fcntl(fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining lock!");
return 0;
}
/*...........*/
wBytes=write(fd,&(*my_faculty),sizeof(*my_faculty));
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

/*
Create/ Save new faculty:: Update to file...
*/

int save_faculty(struct faculty *my_faculty){
int faculty_id;
int rBytes,wBytes, fd, offset;
faculty_id=get_record_details(0);
if(faculty_id==-1) return -1;

my_faculty->fact_id=faculty_id;
fd=open("./records/faculty_file",O_WRONLY | O_CREAT,0777);
if(fd==-1){
perror("Cannot Open File");
return -1;
}
offset=lseek(fd,faculty_id*sizeof(struct faculty),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in faculty File");
return -1;
}
/*Setting Lock*/
struct flock lock = {F_WRLCK, SEEK_SET, faculty_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
int lockingStatus = fcntl(fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining lock!");
return -1;
}
/*...........*/
wBytes=write(fd,&(*my_faculty),sizeof(*my_faculty));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/
if(wBytes<=0){
perror("Cannot write into the file");
return -1;
}
close(fd);

//upadate available account-no...
if(!set_record_details(0,faculty_id+1)){
printf("Error while updating record file\n");
return -1;
}

//success...
return faculty_id;
}

