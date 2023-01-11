#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int BUF_SIZE = 1024;

int main(int argc, char **argv){
    int serv_sock,clnt_sock;
    FILE* readfp;
    FILE* writefp;

    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    char buf[BUF_SIZE] = {0,};

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    bind(serv_sock,(struct sockaddr *)&serv_adr,sizeof(serv_adr));
    listen(serv_sock,5);
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_adr,&clnt_adr_sz);

    readfp = fdopen(clnt_sock, "r");
    writefp = fdopen(dup(clnt_sock), "w");
    
    fputs("FROM SERVER: hi client? \n",writefp);
    fputs("I LOVE all of world\n",writefp);
    fputs("You are awesome \n",writefp);
    fflush(writefp);

    shutdown(fileno(writefp),SHUT_WR);
    fclose(writefp);

    fgets(buf,sizeof(buf),readfp);
    fputs(buf,stdout);
    fclose(readfp);
    return 0;
}
