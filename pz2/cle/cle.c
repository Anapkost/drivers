#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int foo;
	foo = open("/dev/serv", O_RDWR);
	if(foo < 0)
		printf("error");
	char tmp[6];
	read(foo, tmp, 6);
	for(int i = 0; i < 5; i++){
		printf("%c", tmp[i]);
	}
	close(foo);
	return 0;
}
