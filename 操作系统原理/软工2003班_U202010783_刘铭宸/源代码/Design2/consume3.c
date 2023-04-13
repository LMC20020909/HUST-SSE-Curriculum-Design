#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

char buffer[64];
#define DEV_NAME "/dev/BlockFIFODevV3"
int main() {
    int fd = open(DEV_NAME, O_RDWR | O_NONBLOCK);
    if (fd < 0) {
		printf("open %s failded\n", DEV_NAME);
		return -1;
	}
    pid_t pid = getpid();
    while(1) {
        int Num = rand() % 8 + 5;
        while(read(fd, buffer, Num) == 0)
            printf("consume3 pid = %d 申请读出%d字符\n", pid, Num);
    }
	close(fd);
	return 0;
}
