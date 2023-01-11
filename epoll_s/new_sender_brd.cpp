#include <asm-generic/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
const int BUF_SIZE = 30;
void error_handling(const char *message);

int main(int argc, char **argv){
    int send_sock;
    struct sockaddr_in broad_adr;
    FILE *fp;
    char buf[BUF_SIZE];
    int so_brd = 1;

    if(argc != 3){
        printf("Usage: %s<Boradcase  IP><PORT>\n",argv[0]);
        exit(1);
    }
    send_sock = socket(AF_INET, SOCK_DGRAM,0);
    bzero(&broad_adr, sizeof(broad_adr));
    broad_adr.sin_family = AF_INET;
    broad_adr.sin_addr.s_addr = inet_addr(argv[1]);
    broad_adr.sin_port = htons(atoi(argv[2]));

    setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void *)&so_brd,sizeof(so_brd));
    if((fp = fopen("news.txt","r")) == NULL) {
        error_handling("fopen error");
    }
    
    while(!feof(fp)) {
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock,buf,strlen(buf),0,(struct sockaddr*)&broad_adr,sizeof(broad_adr));
        sleep(2);
    }
    close(send_sock);
    return 0;
}

void error_handling(const char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
