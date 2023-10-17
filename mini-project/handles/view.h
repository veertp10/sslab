/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
view the student/faculty details.
view the courses offered by the faculty.
view the courses student enrolled.
*/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include<time.h>



void view_student_handle(int cfd){
struct student my_student;
struct message msg;
int id;
int readBytes, writeBytes;
write_msg(cfd,1,0,"\nEnter Login-id: ");
read_msg(cfd,&msg);

id=atoi(msg.body);

my_student=get_student_details(id);
if(my_student.stud_id==-1){
write_msg(cfd,0,1,"\nCannot view the Student...");
return;
}

char buffer[1000];
sprintf(buffer,"...................Student Details..................\nName: %s\nLogin-Id: %s\nPassword: %s\nActive : %d",my_student.stud_name,my_student.stud_login_id,my_student.stud_password,my_student.stud_status);
write_msg(cfd,0,1,buffer);

}

void view_faculty_handle(int cfd){
struct faculty my_faculty;
struct message msg;
int id;
int readBytes, writeBytes;
write_msg(cfd,1,0,"\nEnter Login-id: ");
read_msg(cfd,&msg);

id=atoi(msg.body);

my_faculty=get_faculty_details(id);
if(my_faculty.fact_id==-1){
write_msg(cfd,0,1,"\nCannot view the Faculty...");
return;
}

char buffer[1000];
sprintf(buffer,"...................Faculty Details..................\nName: %s\nLogin-Id: %s\nPassword: %s\n",my_faculty.fact_name,my_faculty.fact_login_id,my_faculty.fact_password);
write_msg(cfd,0,1,buffer);

}



void view_offering_course(int cfd,int faculty_id){
struct faculty my_faculty;
struct message msg;
my_faculty=get_faculty_details(faculty_id);
if(my_faculty.fact_id==-1){
write_msg(cfd,0,1,"\nCannot view the faculty...");
return;
}
if(my_faculty.n_courses==0){
write_msg(cfd,0,1,"\nNo courses to display ");
return;
}
for(int i=0;i<my_faculty.n_courses;i++){
int course_no=my_faculty.courses[i];
struct course my_course;
my_course=get_course_details(course_no);
if(my_course.course_id==-1){
write_msg2(cfd,0,1,"\nCannot view the course...",course_no);
}
char buffer[1000];
sprintf(buffer,"\nName: %s\tcourse-Id: %d\tfaculty-name: %s\tclass-size:%d\n",my_course.course_name,my_course.course_id,my_faculty.fact_name,my_course.max_slots);
write_msg(cfd,0,1,buffer);
}
write_msg(cfd,0,1,"\n.....................................\n");
}

void view_all_course(int cfd){
int n2 = get_record_details(0);
for(int i=0;i<n2;i++){
view_offering_course(cfd,i);
}
}

void view_enrolled_courses(int cfd,int student_id){
struct student my_student;
struct message msg;
my_student=get_student_details(student_id);
if(my_student.stud_id==-1){
write_msg(cfd,0,1,"\nCannot view the student...");
return;
}
if(my_student.n_enrolls==0){
write_msg(cfd,0,1,"\nNo enrolls to display ");
return;
}
for(int i=0;i<5;i++){
int course_no=my_student.enrolls[i];
struct course my_course;
my_course=get_course_details(course_no);
if(my_course.course_id==-1){
write_msg2(cfd,0,1,"\nCannot view the course...",course_no);
}
char buffer[1000];
sprintf(buffer,"\nName: %s\tcourse-Id: %d\n",my_course.course_name,my_course.course_id);
write_msg(cfd,0,1,buffer);
}
write_msg(cfd,0,1,"\n.....................................\n");
}

