#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int ptoc_fd[2], ctop_fd[2];
    pipe(ptoc_fd);
    pipe(ctop_fd);
    char buf[8];
    int pid = fork();
    if (pid == 0){
        read(ptoc_fd[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(ctop_fd[1], "pong", strlen("pong"));
    }
    else{
        write(ptoc_fd[1], "ping", strlen("ping"));
        wait((int *)0);
        read(ctop_fd[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}