/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
admin_menu(int cfd):gives all functionalities of the admin.
faculty_menu(int cfd,int id):gives all the functionalities of the faculty.
student_menu(int cfd,int id):gives all the functionalities of the student.
*/

void admin_menu(int cfd){

struct message msg;
int readBytes, writeBytes;
begin2:
write_msg(cfd,1,0,"\n....... Welcome to Admin Menu .......\n1. Add Student\n2. view Student\n3. Add Faculty\n4. view Faculty\n5. Activate Student\n6. Deactivate Student\n7. modify Faculty details\n8. modify Student details\n9. / any key to Logout/Exit\nEnter Your Choice:");
read_msg(cfd,&msg);
int choice=atoi(msg.body);
switch(choice){
case 1: add_student_handle(cfd); 	
	goto begin2;
	break;
case 2: view_student_handle(cfd); 	
	goto begin2; 
	break;
case 3: add_faculty_handle(cfd); 	
	goto begin2; 
	break;
case 4: view_faculty_handle(cfd); 	
	goto begin2; 
	break;
case 5: 
	write_msg(cfd,1,0,"\nEnter Login-id: ");
	read_msg(cfd,&msg);
	
	if(activate_student(atoi(msg.body))){
	write_msg(cfd,0,1,"\nStudent Activation Successful! ");
	}
	else{
	write_msg(cfd,0,1,"\nError while Activating! ");
	}
	goto begin2; 
	break;
case 6: 
	write_msg(cfd,1,0,"\nEnter Login-id: ");
	read_msg(cfd,&msg);
	
	if(deactivate_student(atoi(msg.body))){
	write_msg(cfd,0,1,"\nStudent De-activation Successful! ");
	}
	else{
	write_msg(cfd,0,1,"\nError while De-activating! ");
	}
	goto begin2; 
	break;
case 7: modify_faculty_details(cfd);
	goto begin2; 
	break;
case 8: modify_student_details(cfd);
	goto begin2; 
	break;

default:
	write_msg(cfd,0,0,"");
	break;
}

}


void faculty_menu(int cfd,int id){

struct message msg;
int readBytes, writeBytes;
begin3:
write_msg(cfd,1,0,"\n....... Welcome to Faculty menu .......\n1. Add new Course\n2. Remove offered Course\n3. View offered Courses\n4. Password Change\n5. / any key to Exit\nEnter Your Choice:");
read_msg(cfd,&msg);
int choice=atoi(msg.body);
switch(choice){
case 1: add_course_handle(cfd); 	
	goto begin3;
	break;
case 2: write_msg(cfd,1,0,"\nEnter course-id: ");
	read_msg(cfd,&msg);
	
	if(remove_offered_course(atoi(msg.body))){
	write_msg(cfd,0,1,"\ncourse removed Successful! ");
	}
	else{
	write_msg(cfd,0,1,"\nError while removing course! ");
	}
	goto begin3; 
	break;
case 3: view_offering_course(cfd,id); 	
	goto begin3; 
	break;
case 4: modify_faculty_password(cfd,id); 	
	goto begin3; 
	break;

default:
	write_msg(cfd,0,0,"");
	break;
}
}



void student_menu(int cfd,int id){

struct message msg;
int readBytes, writeBytes;
begin4:
write_msg(cfd,1,0,"\n....... Welcome to Student menu .......\n1.view all courses\n2. Enroll to new Courses\n3. drop course\n4. View enrolled Courses\n5. Password Change\n6. / any key to Exit\nEnter Your Choice:");
read_msg(cfd,&msg);
int choice=atoi(msg.body);
switch(choice){
case 1: view_all_course(cfd); 	
	goto begin4;
	break;
case 2: enroll_course(cfd,id); 	
	goto begin4;
	break;
case 3: drop_course(cfd,id); 	
	goto begin4; 
	break;
case 4: view_enrolled_courses(cfd,id); 	
	goto begin4; 
	break;
case 5: modify_student_password(cfd,id); 	
	goto begin4; 
	break;

default:
	write_msg(cfd,0,0,"");
	break;
}


}




