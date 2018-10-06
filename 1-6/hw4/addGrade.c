#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

#define BUF_SIZE 4096

int main()
{

    int outputFd;
    int ret;
    ssize_t numIn, numOut;
    char buffer[BUF_SIZE];

    outputFd = open("grade", O_RDWR | O_CREAT |O_APPEND, S_IRUSR| S_IWUSR);
    write(1,"File opened\n",12);
    write(1,"If you want to enter grade please type y\n",41);
    //every time enter the grade should type "y" first,then do lock_ex.
    //others can not enter at the same time .
    //if finish then type e to unlock the file.Then others can enter.

    while((numIn=read (1, buffer, BUF_SIZE)) > 0)
    {
        if(buffer[0]=='y')
        {
            if(flock(outputFd,LOCK_EX|LOCK_NB)==-1)
            {//others can not enter grade while you are entering.
                write(1,"Others enter grade now,please wait\n",35);
                write(1,"If you want to enter grade please type y\n",41);
            }
            else //not until typing "e",you can enter.
            {
                write(1,"Enter end please type e\n",24);
                flock(outputFd,LOCK_EX);
                while((numIn=read (1, buffer, BUF_SIZE)) > 0)
                {
                    if(buffer[0]=='e') break;
                    numOut= write (outputFd, buffer, (ssize_t) numIn);
                }
                flock(outputFd,LOCK_UN);
                write(1,"If you want to enter grade please type y\n",41);
            }
        }

        else
        {//if someone wants to enter grade but did not type "y".
         //check if it is locked or not,and show the detail on the screen.
         //if it is unlock,the enter is valid.
            if(flock(outputFd,LOCK_EX|LOCK_NB)==-1)
            {
                write(1,"Exclusive lock now\n",19);
            }
            else if(flock(outputFd,LOCK_SH|LOCK_NB)==-1)
            {
                write(1,"Shared lock now\n",16);
            }
            else if(flock(outputFd,LOCK_UN)==0)
            {
                write(1,"Unlock now\n",11);
                flock(outputFd,LOCK_EX);
                numOut= write (outputFd, buffer, (ssize_t) numIn);
                flock(outputFd,LOCK_UN);
            }
        }
    }
    close (outputFd);
}
