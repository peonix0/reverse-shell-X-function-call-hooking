// reverse shell server code goes here


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/user.h>


int portno = 13655;

void error(char *msg){
    perror(msg);
    exit(0);
}

int main(){
    int sockfd, connfd;
    char buf[1024];
    struct sockaddr_in serv_addr, cli_addr;
    

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error, while opening socket\n");
    }
    int on  = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int status = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(status < 0){
        error("Error on binding\n");
    }

    listen(sockfd, 1);

    socklen_t cli_addr_len = sizeof(cli_addr);
    connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
    if(connfd < 0){
        error("Error, while accept\n");
    }
    
    // fcntl(connfd, F_SETFL, O_NONBLOCK|O_RDWR);

    
    // I want non-blocking read 
    int pid = fork();

    if(pid<0){
        error("Error, Couldn't create process\n");
    }
    else if(pid==0){
        // keep read 
        while(1){
            int n = read(connfd, buf, 1024);
            write(1, buf, n);
        }
    }
    else if(pid > 0){
        // input commands
        while(1){  
            int n = read(0, buf,sizeof(buf));
            write(connfd, buf, n); 
        }
    }
    
    close(sockfd);

}