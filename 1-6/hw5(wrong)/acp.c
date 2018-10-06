#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#define BUF_SIZE 4096
int main(int argc, char* argv[]) {
	int file1, file2;
	ssize_t numIn, numOut;
	char buffer[BUF_SIZE];	
	file1 = open (argv [1],O_RDONLY);
	
	char tmpStr[] = "4044101017_XXXXXX";
	mktemp(tmpStr);
	printf("%s is created\n", tmpStr);
	int stream;	
	stream = open(tmpStr,O_WRONLY | O_CREAT, S_IRUSR| S_IWUSR);
	while((numIn=read (file1, buffer, BUF_SIZE)) > 0){
           numOut=write (stream, buffer, (ssize_t) numIn);
   	}
	rename(tmpStr,argv[2]);
	remove(tmpStr);
	
	return 0;
}
