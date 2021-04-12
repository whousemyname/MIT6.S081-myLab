#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	char *errorMes = "no argument!\n";
	if (argc <= 1){
		write(1, errorMes, strlen(errorMes));
		return -1;
	}
	int n = atoi(argv[1]);
	sleep(n);
	exit(0);
	return 0;
}