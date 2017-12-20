#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

int main()
{
    int sockid;
    char msg[50], recv_msg[50];
    struct sockaddr_in sockaddr;

    printf("Enter a msg\n");
    scanf("%s", msg);

    sockid = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(5000);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connecting to server\n");
    connect(sockid, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
   
    printf("Sending message\n");
    send(sockid, msg, 50, 0);

    printf("Receiving message\n");
    recv(sockid, recv_msg, 50, 0);

    printf("%s\n", recv_msg);

    close(sockid);

    return 0;


}