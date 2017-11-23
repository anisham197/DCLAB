// gcc server.c -lpthread -o server
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdlib.h>


typedef struct thread_data {
    int clientid;
    int status;
}thread_data;


void *handler(void *t_data) {
    thread_data* data = (thread_data *)t_data;
    int clientid = data->clientid;
    char buf[50];
    char unlockMessage[50] = "UNLOCKED";
    char lockMessage[50] = "LOCKED";

    // If not locked
    if (!data->status) {

      send(clientid, unlockMessage, 50, 0);
      data->status = 1;
      printf("MUTEX Locked\n");
      printf("Connected to client\n");
      recv(clientid, buf, 50, 0);
      printf("Message Received: %s\n",buf);
      printf("Enter message to send\n");
      scanf("%s", buf);
      send(clientid, buf, 50, 0);
      close(clientid);
      data->status = 0;
      printf("MUTEX unlocked. Disconnected from client\n");
    } 
    else {
      send(clientid, lockMessage, 50, 0);
      close(clientid);
    }
    pthread_exit(NULL);
  }


int main()
{
    int servid, clientid;
    struct sockaddr_in servaddr, clientaddr;
    pthread_t thread;
    int lock = 0;
    char buf[50];

    servid = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Binding server to socket\n");
    bind(servid, (struct sockaddr *)&servaddr, sizeof(servaddr) );

    printf("Listening\n");
    listen(servid, 5);

    thread_data data;
    data.status = lock;

    while(1){
        unsigned int socksize = sizeof(clientaddr);
        clientid = accept(servid, (struct sockaddr *)&clientaddr, &socksize);
        data.clientid = clientid;
        pthread_create(&thread, NULL, handler, (void *)&data);

    }
    close(servid);
    pthread_exit(NULL);
    return 0;
}