#include "kernel/types.h"
#include "user/user.h"

void cleanpipe(int x,int xd[]){
    close(x);
    dup(xd[x]);
    close(xd[0]);
    close(xd[1]);
}

void solve(){
    int fd[2];
    int last, nxt;
    if (read(0, &last, sizeof(int))){
        printf("prime %d\n", last);
        pipe(fd);
        if(fork()==0){
            cleanpipe(1, fd);
            while(read(0,&nxt,sizeof(int))){
                if(nxt % last != 0){
                    write(1, &nxt,sizeof(int));
                }
            }
        }
        else{
            wait((int *)0);
            cleanpipe(0, fd);
            solve();
        }
    }
    
}

int main(int argc,char *argv[]){
    if(argc>1){
        fprintf(2, "Parameter error!");
        exit(1);
    }
    int fd[2];
    pipe(fd);
    if(fork()==0){
        cleanpipe(1, fd);
        for (int i = 2; i < 35; i++){
            write(1, &i, sizeof(int));
        }
    }
    else{
        wait((int *)0);
        cleanpipe(0, fd);
        solve();
    }
    exit(0);
}