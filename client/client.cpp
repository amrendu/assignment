#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>
#define PORT 50000
#define DEST_IP "127.0.0.1"
#define BUFF_SIZE 512
void startConvo(int fd);
//my changes to this code are .....s
using namespace std;
/*
Client implementation of network socket */

int main()
{
    int cfd;
    struct sockaddr_in client_addr;
    /* 1. careate socket */
    if( (cfd= socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket syscall failed ");
        return 0;
    }

    cout<<"Socket created successfully fd= "<<cfd<<endl;
   
    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=inet_addr(DEST_IP);
    client_addr.sin_port=htons(PORT);
   
   cout<<"Connecting to server .....\n";

   if(connect(cfd,(struct sockaddr *)&client_addr,sizeof(client_addr)) <0 )
   {
       perror("Connect failed ..:(");
   }
    else
    {
        cout<<"Connected to server .. :)\n";
        //startConvo(cfd);
        
        char sendbuff[BUFF_SIZE]="distance=12&direction=N&speed=85&time=1220&carID=1254545\n";
        send(cfd,sendbuff,BUFF_SIZE,0);
        cout<<"sent to server";


    }


    return 0;
}


