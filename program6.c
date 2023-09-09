#include <stdio.h>
#include <unistd.h>
#define n 10

int main() {
    char buffer[n];
    ssize_t value;

    while ((value = read(0, buffer,n)) > 0) {
        write(1, buffer,value);
    
   if(value<0)
   {
      return 1;
   }
   }
    return 0;
}

