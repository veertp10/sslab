/*
Author: VEERENDRAGOUDA.T.PATIL
File Description: 
login page for the admin,faculty,student.
*/

bool admin_login(char* id,char* password) {
	char loginid[10] = "iiitb";
	char passwd[10] = "sslab";
	if(strcmp(id,loginid) == 0 && strcmp(password,passwd) == 0)
	return 1;
return 0;
}
bool student_login(char* id,char* password){
	struct student my_student;
	my_student=get_student_details(atoi(id));
	if(my_student.stud_id==-1)return 0;
	if(strcmp(my_student.stud_login_id,id)==0 && strcmp(my_student.stud_password,password)==0){
	return 1;
	}
return 0;
}
bool faculty_login(char* id,char* password){
	struct faculty my_faculty;
	my_faculty=get_faculty_details(atoi(id));
	if(my_faculty.fact_id==-1)return 0;
	if(strcmp(my_faculty.fact_login_id,id)==0 && strcmp(my_faculty.fact_password,password)==0){
	return 1;
	}
return 0;
}

void login_handle(int cfd, int type) {
    struct message msg;
    char id[11];
    char password[11];
    int readBytes, writeBytes;
    
    // Login Menu
    // Getting Login_id
    write_msg(cfd, 1, 0, "\nEnter Login-Id: ");
    read_msg(cfd, &msg);
    strcpy(id, msg.body);
    id[10] = '\0';

    // Getting Password
    write_msg(cfd, 1, 2, "\nEnter Password: ");
    read_msg(cfd, &msg);
    strcpy(password, msg.body);
    password[10] = '\0';

    if (type == 0 && admin_login(id, password)) {
        write_msg(cfd, 0, 1, "\nLogin Successful! ");
        // Goto menu
        admin_menu(cfd);
    } else if (type == 1 && faculty_login(id, password)) {
        write_msg(cfd, 0, 1, "\nLogin Successful! ");
        // Goto menu
        faculty_menu(cfd, atoi(id));
    } else if (type == 2 && student_login(id, password)) {
        write_msg(cfd, 0, 1, "\nLogin Successful! ");
        // Goto menu
        student_menu(cfd,atoi(id));
    } else {
        write_msg(cfd, 1, 0, "\nLogin Failed: Invalid Details or Already Logged in...\nDo you want to Try again(Y/N): ");
        read_msg(cfd, &msg);

        if ((msg.body[0] == 'Y' && msg.body[1] == '\0') || (msg.body[0] == 'y' && msg.body[1] == '\0')) {
            login_handle(cfd, type);
        } else {
            write_msg(cfd, 0, 0, "");
        }
    }
}


