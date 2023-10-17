/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
is_validId(int type, int id) :To check whether given id is valid or not by checking in record file.
get_record_details(int type) :To get count of appropriate record details.
set_record_details(int type, int value) : Method to set count of record details.
*/

bool is_validId(int type, int id){
if(id<0) return 0;
struct record my_record;
int record_fd, rBytes, offset;
record_fd=open("./records/record_file",O_RDONLY);
if(record_fd==-1){
perror("Cannot Open File");
return 0;
}
offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in Record File");
return 0;
}

/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on Account record!");
return 0;
}
/*...........*/
rBytes=read(record_fd,&my_record,sizeof(my_record));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(record_fd, F_SETLK, &lock);
/*...........*/
if(rBytes<=0){
perror("Cannot read the file");
return 0;
}
switch(type){
case 0: if(id>=my_record.faculty) return 0;
	break;
case 1: if(id>=my_record.student) return 0;
	break;
case 2: if(id>=my_record.course) return 0;
	break;

default: return 0;
	break;
}

close(record_fd);
return 1;
}

//Record Details Getters and Setters.....
int get_record_details(int type){
struct record my_record;
int record_fd,rBytes,retVal, offset;
record_fd=open("./records/record_file",O_RDONLY);
if(record_fd==-1){
perror("Cannot Open File");
return -1;
}
offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in Record File");
return -1;
}

/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on Account record!");
return 0;
}
/*...........*/
rBytes=read(record_fd,&my_record,sizeof(my_record));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(record_fd, F_SETLK, &lock);
/*...........*/
if(rBytes<=0){
perror("Cannot read the file");
return -1;
}
// Body.................
switch(type){
case 0: retVal=my_record.faculty;
	break;
case 1: retVal=my_record.student;
	break;
case 2: retVal=my_record.course;
	break;


default: return -1;
	break;
}

close(record_fd);
return retVal;
}

bool set_record_details(int type, int value){
struct record my_record;
int record_fd,rBytes,wBytes, offset;
//open...
record_fd=open("./records/record_file",O_RDWR);
if(record_fd==-1){
perror("Cannot Open File");
return 0;
}
//read...
offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in Record File");
return 0;
}

/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on Account record!");
return 0;
}
/*...........*/
rBytes=read(record_fd,&my_record,sizeof(my_record));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(record_fd, F_SETLK, &lock);
/*...........*/

if(rBytes<=0){
perror("Cannot read the file");
return 0;
}
// Body.................
switch(type){
case 0: my_record.faculty=value;
	break;
case 1: my_record.student=value;
	break;
	
case 2: my_record.course=value;
	break;
default: return 0;
	break;
}
//update....
offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
if(offset==-1){
perror("Error while Repositioning in Record File");
return 0;
}

/*Setting Lock*/
lock.l_type = F_WRLCK;
lock.l_start = 0*sizeof(struct record);
lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
if (lockingStatus == -1)
{
perror("Error obtaining read lock on Account record!");
return 0;
}
/*...........*/
wBytes=write(record_fd,&my_record,sizeof(my_record));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(record_fd, F_SETLK, &lock);
/*...........*/
if(wBytes<=0){
perror("Cannot write into the file");
return 0;
}

close(record_fd);
return 1;
}
