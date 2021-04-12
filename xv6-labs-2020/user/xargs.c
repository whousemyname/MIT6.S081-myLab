#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


int main(int argc, char *argv[]){


	int k;
	char buff[32];
	char lineChar[32];
	int lcIndex = 0;
	char *strPoint = lineChar;
	char *myArgv[32];
	int maIndex = 0;
	int i;
	for (i = 1; i < argc; i++){
		myArgv[maIndex++] = argv[i];
	}
	while ((k = read(0, buff, sizeof(buff))) > 0){
		int j;
		for (j = 0; j < k; j++){
			if (buff[j] == '\n'){
				lineChar[lcIndex++] = 0;
				myArgv[maIndex++] = strPoint;
				myArgv[maIndex] = 0;
				maIndex = argc - 1;
				lcIndex = 0;
				strPoint = lineChar;
				if (fork() == 0){
					exec(myArgv[0], myArgv);
				}
				wait(0);
			}else if (buff[j] == ' '){	
				lineChar[lcIndex++] = 0;
				myArgv[maIndex++] = strPoint;
				strPoint = &lineChar[lcIndex];
			}else {
				lineChar[lcIndex++] = buff[j];
			}
		}
	}
	exit(0);
}
