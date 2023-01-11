#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int BUF_SIZE = 30;
void error_handler(const char*message);

int main(int argc, char** argv){
    int recv_sock;
    struct sockaddr_in adr;
    int str_len;
    char buf[BUF_SIZE];
    if(argc != 2){
        printf("Usage: %s<PORT>\n",argv[0]);
        exit(1);
    }
    recv_sock = socket(AF_INET, SOCK_DGRAM,0);
    memset(&adr,0,sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[1]));

    if(bind(recv_sock,(struct sockaddr *)&adr,sizeof(adr)) == -1)
        error_handler("bind error");
    while(1){
        str_len = recvfrom(recv_sock,buf,BUF_SIZE-1,0,NULL,0);
        if(str_len < 0)
            break;
        buf[str_len] = 0;
        fputs(buf,stdout);
    }
    close(recv_sock);
    return 0;
}
void error_handler(const char*message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
