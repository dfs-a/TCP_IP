#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

const int BUF_SIZE = 30;
void error_handling(string message);

int main(int argc, char **argv){
    int sock;
    char msg1[] = "Hi!";
    char msg2[] = "I'm another UDP host!";
    char msg3[] = "Nice to meet you";

    struct sockaddr_in your_adr;
    socklen_t your_adr_sz;
    if(argc != 3){
        printf("Usage:%s<IP><Port>\n",argv[0]);
        exit(1);
    }
    
    sock = socket(AF_INET, SOCK_DGRAM,0);
    if(sock == -1)
        error_handling("socket error");
    memset(&your_adr,0,sizeof(your_adr));
    your_adr.sin_family = AF_INET;
    your_adr.sin_port = htons(atoi(argv[2]));
    your_adr.sin_addr.s_addr = inet_addr(argv[1]);

    sendto(sock,msg1,sizeof(msg1),0,(struct sockaddr*)&your_adr,sizeof(your_adr));
    sendto(sock,msg2,sizeof(msg2),0,(struct sockaddr*)&your_adr,sizeof(your_adr));
    sendto(sock,msg3,sizeof(msg3),0,(struct sockaddr*)&your_adr,sizeof(your_adr));
    close(sock);
    return 0;
}

void error_handling(string message) {
    fputs((char*)&message,stderr);
    fputc('\n',stderr);
    exit(1);
}
