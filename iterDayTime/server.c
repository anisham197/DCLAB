#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int servid, msglen;
    unsigned int socksize;
    char msg[50];
    struct sockaddr_in servaddr, clientaddr;
    pid_t pid;
    time_t currenttime;

    servid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Binding to server to socket\n");
    bind(servid, (struct sockaddr *)&servaddr, sizeof(servaddr) );

    while(1){
        socksize = sizeof(clientaddr);
        msglen = recvfrom(servid, msg, 50, 0, (struct sockaddr *)&clientaddr, &socksize);

        if ( msglen >= 0){
            sleep(2);
            printf("Sending message\n");
            time(&currenttime);
            sendto(servid,ctime(&currenttime) , 50, 0, (struct sockaddr *)&clientaddr, socksize);
        }
    }
    close(servid);
    return 0;
}