#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd; 
    char buf[100];
    fd = open("/dev/mogus_char",O_RDWR);
    
    
    read(fd,buf,100);

    printf("GOT FROM DRIVER:  %s \n",buf);
  close(fd);
}
