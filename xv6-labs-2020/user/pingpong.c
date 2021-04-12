#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]){
	int p[2], p2[2];
	pipe(p);
	pipe(p2);
	char buff[5];
	int pid = fork();
	if (pid == 0){	//child
		read(p[0], buff, 4);
		printf("%d: received ping\n", getpid());
		write(p2[1], "pong", 4);
		close(p[0]);
		close(p[1]);
		close(p2[0]);
		close(p2[1]);
		exit(0);
	}else {	//parent
		write(p[1], "ping", 4);
		read(p2[0], buff, 4);
		printf("%d: received pong\n", getpid());
		close(p[0]);
		close(p[1]);
		close(p2[0]);
		close(p2[1]);
	}
	return 0;
}