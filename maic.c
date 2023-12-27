#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>   
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <sys/ioctl.h>

#define MAX_USER_INPUT_SIZE 10

int main() {
int fd;
char message_to_send[MAX_USER_INPUT_SIZE] = "Hello";

fd = open("/dev/net0",O_RDWR);
	if (fd < 0) {
	perror("Ошибка при открытии файла с драйвером");
	return -1;
	}	

	if (ioctl(fd, 0, message_to_send) < 0) {
	perror("Ошибка при использовании ioctl");
	return -1;
	}

close(fd);
return 0;
}
