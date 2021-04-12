#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int buff[34];
void func(int *fd, int index){
	int i;
	for (i = 0; i < index; i++){
		read(fd[0], buff + i, sizeof(int) * 1);
	}
	close(fd[0]);
	close(fd[1]);
	if (index == 1){
		printf("prime %d\n", buff[0]);
		exit(0);
	}
	printf("prime %d\n", buff[0]);
	int fd2[2], index2 = 0, childStatus;
	pipe(fd2);
	for (i = 1; i < index; i++){
		if ((buff[i] % buff[0]) != 0){
			write(fd2[1], buff + i, sizeof(int) * 1);
			index2++;
		}
	}
	if (fork() == 0){	//child
		func(fd2, index2);
		close(fd2[0]);
		close(fd2[1]);
		exit(0);
	}else {
		wait(&childStatus);
		exit(0);
	}
}


int main(int argc, char *argv[]){
	int i;
	for (i = 0; i < 34; i++){
		buff[i] = i + 2;
	}
	int fd[2];
	pipe(fd);
	write(fd[1], buff, sizeof(int) * 34);
	func(fd, 34);
	close(fd[0]);
	close(fd[1]);
	return 0;
}