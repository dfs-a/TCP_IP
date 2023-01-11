#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
const int BUF_SIZE = 30;

int main(int argc, char **argv){
    fd_set reads,temps;
    int result,str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    FD_ZERO(&reads);
    FD_SET(0,&reads);

    while(1){
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1,&temps,NULL,NULL,&timeout);
        if(result == -1){
            puts("select() error");
            break; 
        }else if(result == 0){
            puts("timeout");
        }else{
            if(FD_ISSET(0,&reads)){
                str_len = read(0,buf,BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s",buf);
            }
        }
    }
    return 0;
}
