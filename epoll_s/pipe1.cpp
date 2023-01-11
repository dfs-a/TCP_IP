#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
const int BUF_SIZE = 30;

int main(int argc, char **argv){
    int fds[2];
    const char str[] = "Who are you?";
    char buf[BUF_SIZE];
    pid_t pid;
    int state;
    pipe(fds);
    pid = fork();
    if(pid == 0){
        write(fds[1],str,sizeof(str));
    }else{
        read(fds[0],buf,BUF_SIZE);
        puts(buf);
        wait(&state);
    }
    return 0;
}
