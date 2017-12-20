#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

int main()
{
    int sockid;    
    unsigned int socksize;
    char msg[50], recv_msg[50];
    struct sockaddr_in sockaddr;

    printf("Enter a msg\n");
    scanf("%s", msg);

    sockid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(5000);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socksize = sizeof(sockaddr);

    printf("Sending message\n");
    sendto(sockid, msg, 50, 0, (struct sockaddr *)&sockaddr, socksize);

    printf("Receiving message\n");
    recvfrom(sockid, recv_msg, 50, 0, (struct sockaddr *)&sockaddr, &socksize);

    printf("%s\n", recv_msg);

    close(sockid);

    return 0;
}