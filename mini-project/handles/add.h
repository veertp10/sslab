/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
add the details of the student,faculty,course.
enroll/drop the course.
*/


void add_student_handle(int cfd){
int student_id;
struct student my_student;
struct message msg;
int readBytes, writeBytes;

//Getting details
write_msg(cfd,1,1,"\nEnter Name: ");
read_msg(cfd,&msg);

strcpy(my_student.stud_name,msg.body);


write_msg(cfd,1,0,"\nEnter activation status (1-active , 0-deactive): ");
read_msg(cfd,&msg);

my_student.stud_status=atoi(msg.body);

write_msg(cfd,1,2,"\nEnter Password: # ");
read_msg(cfd,&msg);

strcpy(my_student.stud_password,msg.body);

//Initializing...
strcpy(my_student.stud_login_id,"");
//Update to file
student_id=save_student(&my_student);
if(student_id==-1){
write_msg(cfd,0,1,"\nCannot Save the Student...");
return;
}
else{
write_msg2(cfd,0,1,"\nStudent Created Successfully!\nNote: Login-Id is {student-Id.}\n",student_id);
}
//set Login-Id...
sprintf(my_student.stud_login_id,"%d",student_id);
bool status=set_student_details(student_id,&my_student);
if(status==0){
write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
}
else{
write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id:",student_id);
}
}



void add_faculty_handle(int cfd){
int faculty_id;
struct faculty my_faculty;
struct message msg;
int readBytes, writeBytes;

//Getting details
write_msg(cfd,1,1,"\nEnter Name: ");
read_msg(cfd,&msg);

strcpy(my_faculty.fact_name,msg.body);

write_msg(cfd,1,2,"\nEnter Password: # ");
read_msg(cfd,&msg);

strcpy(my_faculty.fact_password,msg.body);

//Initializing...
strcpy(my_faculty.fact_login_id,"");
my_faculty.n_courses=0;
for(int i=0;i<5;i++)
my_faculty.courses[i]=-1;
//Update to file
faculty_id=save_faculty(&my_faculty);
if(faculty_id==-1){
write_msg(cfd,0,1,"\nCannot Save the faculty...");
return;
}
else{
write_msg2(cfd,0,1,"\nfaculty Created Successfully!\nNote: Login-Id is {faculty-Id.}\n",faculty_id);
}
//set Login-Id...
sprintf(my_faculty.fact_login_id,"%d",faculty_id);
bool status=set_faculty_details(faculty_id,&my_faculty);
if(status==0){
write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
}
else{
write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id:",faculty_id);
}
}





void add_course_handle(int cfd){
int course_no;
struct course my_course;
struct message msg;
struct faculty my_faculty;
int rwstatus, fid;
int n1, n2;
//Getting details
//Getting details
write_msg(cfd,1,1,"\nEnter Name of the course: ");
read_msg(cfd,&msg);

strcpy(my_course.course_name,msg.body);

//Getting details
write_msg(cfd,1,1,"\nEnter credits: ");
read_msg(cfd,&msg);

my_course.course_credits = atoi(msg.body);

write_msg(cfd,1,1,"\nEnter no.of students allowed for this couse: ");
read_msg(cfd,&msg);
my_course.max_slots = atoi(msg.body);


rwstatus=write_msg(cfd,1,0,"\nEnter fact-Id: ");
if(!rwstatus){
perror("Error while writing...");
return;
}
rwstatus=read_msg(cfd,&msg);
if(!rwstatus){
perror("Error while reading...");
return;
}
fid=atoi(msg.body);

if(is_validId(0,fid)){

//Setting Semaphore Details...
key_t semKey;      
int semIdentifier; 
int semctlStatus;  
int semopStatus;  

    union semun
    {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf; 
    } semSet;

    semKey = ftok(".", 121);
    if (semKey == -1)
    {
        perror("Error while getting key!");
        return;
    }

    semIdentifier = semget(semKey, 1, 0);
    if (semIdentifier == -1)
    {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700);
        if (semIdentifier == -1)
        {
            perror("Error while semaphore creation...");
            return;
        }

        semSet.val = 1; 
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while binary semaphore initialization...");
            return;
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_op = -1;
    semOp.sem_flg = SEM_UNDO;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error: semaphore opn failed...");
        return;
    }
/*
Critical Section..............Start
*/
my_faculty=get_faculty_details(fid);
if(my_faculty.n_courses==5){
write_msg(cfd,0,1,"\nMax-Limit of courses Reached...");
 
/*
Critical Section................End
*/
// unlocking the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        return;
    }
return;
}

my_faculty.courses[my_faculty.n_courses]=fid;
n1=my_faculty.n_courses;
my_faculty.n_courses+=1;
set_faculty_details(fid,&my_faculty);


/*
Critical Section................End
*/
// unlocking the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        return;
    }
}
else{
write_msg(cfd,0,1,"\nInvalid fact-Id.'s...");
return;
}
my_course.course_faculty=fid;
my_course.course_status=1;


//Update to file
course_no=save_course(&my_course);

if(course_no==-1){
write_msg(cfd,0,1,"\nCannot Save the Account...");
}
else{
my_faculty.courses[n1]=course_no;
set_faculty_details(fid,&my_faculty);
write_msg2(cfd,0,1,"\ncourse Created Successfully!\ncourse No. Generated is",course_no);

}
}







//enroll,drop
void enroll_course(int cfd,int student_id){
struct course my_course;
struct message msg;
struct student my_student;
int rwstatus, cid;
int n1, n2;
//Getting details

rwstatus=write_msg(cfd,1,0,"\nEnter course-Id: ");
if(!rwstatus){
perror("Error while writing...");
return;
}
rwstatus=read_msg(cfd,&msg);
if(!rwstatus){
perror("Error while reading...");
return;
}
cid=atoi(msg.body);

if(is_validId(2,cid)){

//Setting Semaphore Details...
key_t semKey;      
int semIdentifier; 
int semctlStatus;  
int semopStatus;  

    union semun
    {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf; 
    } semSet;

    semKey = ftok(".", 121);
    if (semKey == -1)
    {
        perror("Error while getting key!");
        return;
    }

    semIdentifier = semget(semKey, 1, 0);
    if (semIdentifier == -1)
    {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700);
        if (semIdentifier == -1)
        {
            perror("Error while semaphore creation...");
            return;
        }

        semSet.val = 1; 
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while binary semaphore initialization...");
            return;
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_op = -1;
    semOp.sem_flg = SEM_UNDO;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error: semaphore opn failed...");
        return;
    }
/*
Critical Section..............Start
*/
my_student=get_student_details(student_id);
if(my_student.n_enrolls==6){
write_msg(cfd,0,1,"\nMax-Limit of enrolls Reached,you can't enroll for any course..");
return;
}
my_student.enrolls[my_student.n_enrolls]=cid;
my_student.n_enrolls+=1;


my_course = get_course_details(cid);
if(my_course.max_slots == 0){
write_msg(cfd,0,1,"\nclass is full,you can't enroll for this course..");
return;
}
my_course.max_slots-=1;
set_course_details(cid,&my_course);
set_student_details(student_id,&my_student);
write_msg2(cfd,0,1,"\nsuccessfully enrolled to the course:",cid);




/*
Critical Section................End
*/
// unlocking the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        return;
    }
}
}


/////drop course



void drop_course(int cfd,int student_id){
struct course my_course;
struct message msg;
struct student my_student;
int rwstatus, cid;
int n1;
//Getting details

rwstatus=write_msg(cfd,1,0,"\nEnter course-Id: ");
if(!rwstatus){
perror("Error while writing...");
return;
}
rwstatus=read_msg(cfd,&msg);
if(!rwstatus){
perror("Error while reading...");
return;
}
cid=atoi(msg.body);

if(is_validId(2,cid)){

//Setting Semaphore Details...
key_t semKey;      
int semIdentifier; 
int semctlStatus;  
int semopStatus;  

    union semun
    {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf; 
    } semSet;

    semKey = ftok(".", 121);
    if (semKey == -1)
    {
        perror("Error while getting key!");
        return;
    }

    semIdentifier = semget(semKey, 1, 0);
    if (semIdentifier == -1)
    {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700);
        if (semIdentifier == -1)
        {
            perror("Error while semaphore creation...");
            return;
        }

        semSet.val = 1; 
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while binary semaphore initialization...");
            return;
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_op = -1;
    semOp.sem_flg = SEM_UNDO;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error: semaphore opn failed...");
        return;
    }
/*
Critical Section..............Start
*/
my_student=get_student_details(student_id);
if(my_student.n_enrolls==0){
write_msg(cfd,0,1,"\nnot enrolled in any course..");
return;
}
for(int i=0;i<6;i++){
if(my_student.enrolls[i]==cid){
my_student.enrolls[i]==-1;
my_course = get_course_details(cid);
my_course.max_slots+=1;
set_course_details(cid,&my_course);
write_msg2(cfd,0,1,"\nsuccessfully dropped the course:",cid);
return;
}
}

/*
Critical Section................End
*/
// unlocking the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        return;
    }
}
}


