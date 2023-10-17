/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
gives structure of the record,message,student,faculty,course.
*/


struct record{
int faculty;
int student;
int course;
};

struct message{
int id;
bool type;
int action;
char body[1000];
};



struct student{
int stud_id;
char stud_name[25];
char stud_login_id[11];
char stud_password[11];
bool stud_status;//0-> Inactivate, Other-> Active
int enrolls[6];
int n_enrolls;
};

struct faculty{
int fact_id;
char fact_name[25];
char fact_login_id[11];
char fact_password[11];
int courses[5]; //  array of number of courses offered.
int n_courses;// number of accounts this customer had.
};

struct course{
int course_id;
int course_faculty;// fact.Id's of account holders.
char course_name[25];
int course_credits;
int max_slots;
bool course_status;//0-> Inactivate, Other-> Active
};







