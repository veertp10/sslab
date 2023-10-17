/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
modify student/faculty/course details 
modify student/faculty password
*/


void modify_student_password(int cfd, int id){
struct student my_student;
struct message msg;
int readBytes, writeBytes;

write_msg(cfd,1,2,"\nEnter/ Set New Password: # ");
read_msg(cfd,&msg);

my_student=get_student_details(id);
if(my_student.stud_id==-1){// Anyway this part is never executed...
write_msg(cfd,0,1,"\nInvalid stud-Id...");
return;
}
bzero(my_student.stud_password,sizeof(my_student.stud_password));
strcpy(my_student.stud_password,msg.body);

bool status=set_student_details(id,&my_student);
if(status==0){
write_msg(cfd,0,1,"\nPassword Setting Failed...");
}
else{
write_msg(cfd,0,1,"\nPassword Set Successfully...");
}
}


void modify_student_details(int cfd){
struct student my_student;
struct message msg;
int readBytes, writeBytes;

write_msg(cfd,1,0,"\nEnter stud-Id: ");
read_msg(cfd,&msg);
int id=atoi(msg.body);
my_student=get_student_details(id);
if(my_student.stud_id==-1){
write_msg(cfd,0,1,"\nInvalid stud-Id...");
return;
}
// Getting New Details
write_msg(cfd,1,1,"\nEnter (New) Name: ");
read_msg(cfd,&msg);

strcpy(my_student.stud_name,msg.body);

write_msg(cfd,1,2,"\nEnter (New) Password: # ");
read_msg(cfd,&msg);

strcpy(my_student.stud_password,msg.body);


bool status=set_student_details(id,&my_student);
if(status==0){
write_msg(cfd,0,1,"\nUpdation Failed...");
}
else{
write_msg(cfd,0,1,"\nDetails Updated Successfully...");
}
}

void modify_faculty_password(int cfd, int id){
struct faculty my_faculty;
struct message msg;
int readBytes, writeBytes;

write_msg(cfd,1,2,"\nEnter/ Set New Password: # ");
read_msg(cfd,&msg);

my_faculty=get_faculty_details(id);
if(my_faculty.fact_id==-1){// Anyway this part is never executed...
write_msg(cfd,0,1,"\nInvalid fact-Id...");
return;
}
bzero(my_faculty.fact_password,sizeof(my_faculty.fact_password));
strcpy(my_faculty.fact_password,msg.body);

bool status=set_faculty_details(id,&my_faculty);
if(status==0){
write_msg(cfd,0,1,"\nPassword Setting Failed...");
}
else{
write_msg(cfd,0,1,"\nPassword Set Successfully...");
}
}


void modify_faculty_details(int cfd){
struct faculty my_faculty;
struct message msg;
int readBytes, writeBytes;

write_msg(cfd,1,0,"\nEnter fact-Id: ");
read_msg(cfd,&msg);
int id=atoi(msg.body);
my_faculty=get_faculty_details(id);
if(my_faculty.fact_id==-1){
write_msg(cfd,0,1,"\nInvalid fact-Id...");
return;
}
// Getting New Details
write_msg(cfd,1,1,"\nEnter (New) Name: ");
read_msg(cfd,&msg);

strcpy(my_faculty.fact_name,msg.body);

write_msg(cfd,1,2,"\nEnter (New) Password: # ");
read_msg(cfd,&msg);

strcpy(my_faculty.fact_password,msg.body);


bool status=set_faculty_details(id,&my_faculty);
if(status==0){
write_msg(cfd,0,1,"\nUpdation Failed...");
}
else{
write_msg(cfd,0,1,"\nDetails Updated Successfully...");
}
}



void modify_course_details(int cfd){
struct course my_course;
struct message msg;
int id,readBytes, writeBytes;
write_msg(cfd,1,0,"\nEnter course-id: ");
read_msg(cfd,&msg);
id=atoi(msg.body);

my_course=get_course_details(id);
if(my_course.course_id==-1){
write_msg(cfd,0,1,"\nInvalid  course-id...");
return;
}
// Getting New Details
write_msg(cfd,1,1,"\nEnter (New) course Name: ");
read_msg(cfd,&msg);

strcpy(my_course.course_name,msg.body);

write_msg(cfd,1,1,"\nenter course credits: ");
read_msg(cfd,&msg);

my_course.course_credits = atoi(msg.body);

write_msg(cfd,1,1,"\nenter max students for course: ");
read_msg(cfd,&msg);
my_course.max_slots= atoi(msg.body);

bool status=set_course_details(id,&my_course);
if(status==0){
write_msg(cfd,0,1,"\nUpdation Failed...");
}
else{
write_msg(cfd,0,1,"\nDetails Updated Successfully...");
}
}


