#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
    int servid, clientid;
    char msg[50];
    struct sockaddr_in servaddr, clientaddr;
    pid_t pid;

    servid = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Binding to server to socket\n");
    bind(servid, (struct sockaddr *)&servaddr, sizeof(servaddr) );

    printf("Listening\n");
    listen(servid, 5);
   
    while(1){
        unsigned int socksize = sizeof(clientaddr);
        clientid = accept(servid, (struct sockaddr *)&clientaddr, &socksize);

        printf("Connected to client\n");
        if ( (pid = fork()) == 0){
            recv(clientid, msg, 50, 0);
            printf("Received: %s\n", msg);
            printf("Sending message\n");
            send(clientid, msg, 50, 0);
            close(clientid);
            close(servid);
            exit(0);
        }
        
    }
    close(clientid);
    close(servid);
    return 0;
}