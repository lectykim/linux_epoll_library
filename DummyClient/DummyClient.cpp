//
// Created by user on 24. 1. 7.
//


#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include<string>
#include<chrono>
const int PORT = 7777;
const char* SERVER_IP = "127.0.0.1";

struct PacketHeader
{
    unsigned short size;
    unsigned short id;
};

int main()
{
    int clientSocket = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof (serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) == -1)
    {
        std::cerr<< "Error connecting to server" << std::endl;
        close(clientSocket);
        return -1;
    };
    while(1)
    {
        char* message = "Hello Server";
        PacketHeader packetHeader;
        packetHeader.id=0x0000;
        packetHeader.size=sizeof(message)+sizeof(PacketHeader);
        char * otherMessage = new char[packetHeader.size];
        std::memcpy(otherMessage,&packetHeader,sizeof(packetHeader));
        std::memcpy(otherMessage+sizeof(PacketHeader),message,strlen(message));
        if(send(clientSocket,otherMessage,strlen(message),0)==-1)
        {
            std::cerr<< "Error sending to server" << std::endl;
            close(clientSocket);
            return -1;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        char buffer[1024];
        memset(buffer,0,sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket,buffer,sizeof(buffer)-1,0);
        if(bytesRead == -1)
        {
            std::cerr<<" error receiving data from server"<<std::endl;
            close(clientSocket);
            return -1;
        }

        buffer[bytesRead] = '\0';
        std::cout <<"Data received from server : " << buffer << std::endl;

    }


    close(clientSocket);

    return 0;


}