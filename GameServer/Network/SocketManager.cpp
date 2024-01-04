//
// Created by user on 24. 1. 4.
//

#include "SocketManager.h"

int32 SocketManager::Init() {
    int32 server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0)
    {
        printf("Socket() serror \n");
        return 0;
    }

    //server_fd nonblock socket setting, use edge trigger
    int flags = fcntl(server_fd,F_GETFL);
    flags |= O_NONBLOCK;

    //소켓 옵션 설정 비정상 종료 시 해당 포트 재사용 가능하도록 설정
    int option = true;
    int error_check = setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
    if(error_check<0)
    {
        printf("setsockopt error [%d] \n",error_check);
        close(server_fd);
        return 0;
    }

    struct sockaddr_in mSockAddr;
    memset(&mSockAddr,0,sizeof(mSockAddr));
    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(7777);
    mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); //사용 가능한 ip 사용하기

    error_check = bind(server_fd,(struct sockaddr*)&mSockAddr,sizeof(mSockAddr));
    if(error_check<0)
    {
        printf("bind90 error [%d] \n",error_check);
        close(server_fd);
        return 0;
    }

    listen(server_fd,5);

    return server_fd;
}
