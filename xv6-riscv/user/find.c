#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

char* fmtname(char* path) {
    static char buf[DIRSIZ+1];
    char* p;

    //Find first character after last slash.
    for (p=path+strlen(path); p >= path && *p != '/'; p--)
	;
    p++;

    if (strlen(p) >= DIRSIZ)
	return p;
    memmove(buf, p, strlen(p));
    buf[strlen(p)]='\0';
    return buf;
}

void find(char* path, char* str) {  
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;
    
    if ((fd=open(path, 0)) < 0) {
	fprintf(2, "find: cannot open %s\n", path);
	return;
    }

    if (fstat(fd, &st) < 0) {
	fprintf(2, "find: cannot stat1 %s\n", path);
	close(fd);
	return;
    }

    //printf("this is the current buf: %s, this is path: %s\n", buf, path);
    //printf("path: %s\n", path);
    switch(st.type) {
    case T_DEVICE:
    case T_FILE:
	//printf("file name: %s, cmp name: %s\n", fmtname(path), str);
	if (strcmp(str, fmtname(path))==0) {
	    printf("%s\n", path);
	    break;
	}
	break;
    case T_DIR:
	if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
	    printf("find: path too long\n");
	    break;
	}
    strcpy(buf, path);
    p=buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de))==sizeof(de)){
	if(de.inum==0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
	    continue;
	}

	memcpy(p, de.name, DIRSIZ);
	p[DIRSIZ]=0;
	if(stat(buf, &st) < 0){
	    printf("find: cannot stat %s\n", buf);
	    continue;
	}
	find(buf, str);
    }
    break;
    }
    close(fd);

}

int main(int argc, char **argv)
{
  if (argc < 3) {
    exit(0);
  }
    find(argv[1], argv[2]);
  

  exit(0);
}
