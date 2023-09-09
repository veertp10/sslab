 #include <sys/types.h>
 #include <unistd.h>
 #include <stdio.h>
int main() {
	int pid=fork();
	
	if (pid==0){
		printf("child pid=%d\n",getpid());
	}
	else{
		printf("parent pid=%d\n",getpid());
	}
}


