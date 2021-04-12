#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *obj, char *pathFileName){
	char buff[50], *p;
	struct dirent de;
	struct stat st;
	int fd;

	if ((fd = open(path, 0)) < 0){
		printf("find : cannt open %s\n", path);
		exit(0);
	}

	if (fstat(fd, &st) < 0){
		printf("find : cannt fstat %s\n", path);
		close(fd);
		exit(0);
	}

	switch(st.type){
		case T_FILE:
			if (strcmp(pathFileName, obj) == 0){
				printf("%s\n", path);
			}
			break;
		case T_DIR://open dir, loop every files
			if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buff)){
				printf("find : path is too long!\n");
				break;
			}
			strcpy(buff, path);
			p = buff + strlen(buff);	//strlen(path)
			*p++ = '/';
			while (read(fd, &de, sizeof(de)) == sizeof(de)){
				if (de.inum == 0 || (strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0)){
					continue;
				}
				memmove(p, de.name, DIRSIZ);
				p[DIRSIZ] = 0;
				find(buff, obj, de.name);
			}
			break;
	}
	close(fd);

}

int main(int argc, char* argv[]){
	if (argc < 2){
		printf("argument error!\n");
		exit(0);
	}else if (argc == 2){
		find("/root", argv[1], "/root");
		exit(0);
	}else {
		find(argv[1], argv[2], argv[1]);
		exit(0);
	}
}