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
    int fd = open(DEV_NAME, O_RDWR);
    if (fd < 0) {
		printf("open %s failded\n", DEV_NAME);
		return -1;
	}
    pid_t pid = getpid();
    while(1) {
        int Num = rand() % 8 + 5;
        for(int i = 0; i < Num; i++)
            buffer[i] = rand() % sizeof(char);
        printf("produce1 pid = %d 申请写入%d字符，实际写入%d字符\n", pid, Num, write(fd, buffer, Num));
    }
	close(fd);
	return 0;
}
