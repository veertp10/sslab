#include <stdio.h>
#include <unistd.h>

int main() {
    // Using execl to run the "ls" command
    execl("/bin/ls", "ls", "-l", "/home/user", (char *) NULL);

    // If execl() returns, it means an error occurred
    perror("execl");
    return 1;
}

