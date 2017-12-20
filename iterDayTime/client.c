#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<time.h>

int main()
{
    int sockid;    
    unsigned int socksize;
    char recv_msg[50];
    struct sockaddr_in sockaddr;
    clock_t start, end;

    sockid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(5000);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socksize = sizeof(sockaddr);

    start = clock();
    printf("Sending message\n");
    sendto(sockid, "time", 50, 0, (struct sockaddr *)&sockaddr, socksize);

    printf("Receiving message\n");
    recvfrom(sockid, recv_msg, 50, 0, (struct sockaddr *)&sockaddr, &socksize);
    end = clock();

    printf("%s\n", recv_msg);

    printf("Time Elapsed %f\n", (double)(end - start));

    close(sockid);

    return 0;
}