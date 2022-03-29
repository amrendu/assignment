#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<thread>
#include<string.h>
#include<unistd.h>
#include "FlightCalculator.hpp"
#include <algorithm>
#include <regex>

using namespace std;

class MessageProxy
{
    int sfd,cfd,rc;
    struct sockaddr_in serv_addr,client_addr;
    long int PORT =50000;
    char rcvbuff[512];
    public:
    int init();
    int startServer();
    void recvThread(string msg);
    void sendToFlightCalculatorService(string input);

  

};

void MessageProxy::sendToFlightCalculatorService(string input)
{
    FlightCalculatorService fSvc;
    struct Notification samplePayload;

    std::regex reList("([^=]*)=([^&]*)&?");
    std::for_each( std::sregex_iterator( input.begin(), input.end(), reList ), std::sregex_iterator(),
        [&samplePayload]( std::smatch const& match )
        { 
            string key  = match[1];
            string val = match[2] ;
            std::cout << key << "=" << val<< "\n"; 
            if(key == "distance")
            {
                samplePayload.distance = val;
            }
            else if(key == "direction")
            {
                samplePayload.direction = val;
            }

             else if(key == "speed")
            {
                samplePayload.speed = val;

            }

             else if(key == "time")
            {
                samplePayload.time = val;
                
            }
            else{
                samplePayload.carID = val;

            }
        } );

    
    fSvc.startService();
    samplePayload.printNotification();
    fSvc.postMessage(samplePayload);
}

int  MessageProxy::init()
{
    sfd= socket(AF_INET,SOCK_STREAM,0);
    if(sfd<0)
    {
        perror("socket syscall failed ");
        return 0;
    }
    cout<<"Socket created with fd : "<<sfd<<endl;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(PORT);
    /* 2. bind and address to it */
    rc= bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(rc <0)
    {
        perror("bind failed");
        return 0;
    }
    cout<<"Bind success\n";

    /* 3. listen to socket connections */
    rc=listen(sfd,5);
    if(rc <0)
    {
        perror("listen failed ");
        return 0;
    }
    cout<<"Listen success q 5\n";
    return 1;
}
void MessageProxy::recvThread(string msg)
{
    cout<<"Message from client :";
    cout<<msg<<endl;
    sendToFlightCalculatorService(msg);
    //TODO
    //sendToCollisionCalculatorService(msg);

}
int  MessageProxy::startServer()
{
     socklen_t clientLen=sizeof(client_addr);
    /* accept incoming connections ---> it is blocking call */
    while(1)
    {
        cout<<"waiting for client connection...\n";
        cfd=accept(sfd,(struct sockaddr *)&client_addr,&clientLen);
	    //close(sfd);
        if(rc <-1)
        {
            perror("accept failed ");
            return 0;
        }
        else
        {
            cout<<"Connected to client with fd "<<cfd<<endl;
            recv(cfd,rcvbuff,512,0);
            cout<<"FROM CLIENT :"<<rcvbuff<<endl;
            thread(&MessageProxy::recvThread,this,string(rcvbuff,strlen(rcvbuff))).detach();
        }
    }

}



