#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int main(int argc, char* argv[]){
	
	char buff[50];
	char *str = "woshishabi";
	strcpy(buff, str);
	printf("the result of fmtname is %s\n", fmtname(buff));
	printf("the lenght of fmtname is %d\n", strlen(fmtname(buff)));
	printf("cmp is %d\n", strcmp(fmtname(buff), str));
	exit(0);

}