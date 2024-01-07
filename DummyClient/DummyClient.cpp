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
const int PORT = 7777;
const char* SERVER_IP = "127.0.0.1";

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
        const char* message = "Hello Server";
        if(send(clientSocket,message,strlen(message),0)==-1)
        {
            std::cerr<< "Error sending to server" << std::endl;
            close(clientSocket);
            return -1;
        }

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