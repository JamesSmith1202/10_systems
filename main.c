#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo){
    if(signo == 2){//if SIGINT
        int fd = open("SIGINT.txt", O_CREAT|O_WRONLY|O_APPEND, 0777);
        if(fd == -1){
            printf("OPEN %d: %s\n", errno, strerror(errno));
        }
        char *msg = "Exit due to signal 2: SIGINT\n";
        int len = strlen(msg);
        if(write(fd, msg, len) < len){
            printf("WRITE %d: %s\n", errno, strerror(errno));
        }
        if(close(fd) == -1){
            printf("CLOSE %d: %s\n", errno, strerror(errno));
        }
        exit(0);
    }
    if(signo == 10){//if SIGUSR1
        printf("Parent Process: %d\n", getppid());
    }
}

int main()
{
    while (1)
    {
        signal(2, sighandler);
        signal(10, sighandler);
        printf("Current Process:%d\n", getpid());
        sleep(1);
    }
}