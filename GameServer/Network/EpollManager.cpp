//
// Created by user on 24. 1. 4.
//


#include "EpollManager.h"

int32 EpollManager::EpollInit() {
    if((_fdEpoll=epoll_create(MAX_EVENTS))>0)
        _isEpollInit = true;
    return _isEpollInit;
}

int32 EpollManager::EpollAdd(int32 fd) {
    struct epoll_event ev{};
    ev.events = EPOLLIN|EPOLLET;
    ev.data.fd = fd;
    _socketFd = fd;
    return epoll_ctl(_fdEpoll,EPOLL_CTL_ADD,fd,&ev);
}

void EpollManager::EpollRunning() {
    while(true)
    {
        _eventCount = epoll_wait(_fdEpoll,_events,MAX_EVENTS,_timeout);
        if(_eventCount < 0)
        {
            printf("epoll_wait() error [%d] \n",_eventCount);
        }

        for(int32 i=0;i<_eventCount;i++)
        {
            //Client의 응답이 들어왔을 떄, 해당 함수가 호출된다.
            if(_events[i].data.fd == _socketFd)
            {
                int client_fd;
                int client_len;
                struct sockaddr_in client_addr;

                client_len = sizeof(client_addr);
                client_fd = accept(_socketFd,(struct sockaddr*)&client_addr,(socklen_t*)&client_len);

                //client fd non-blocking socket 으로 설정.
                int flags= fcntl(client_fd,F_GETFL);

                flags |= O_NONBLOCK;
                if(fcntl(client_fd,F_SETFL,flags)<0)
                {
                    printf("client_fd[%d] fcntl error \n",client_fd);
                    return;
                }

                if(client_fd<0)
                {
                    printf("accept() error [%d] \n",client_fd);
                    continue;

                }

                struct epoll_event clientEvents;
                clientEvents.events = EPOLLIN|EPOLLET;
                clientEvents.data.fd = client_fd;

                //클라이언트 fd,epoll에 등록
                if(epoll_ctl(_fdEpoll,EPOLL_CTL_ADD,client_fd,&clientEvents)<0)
                {
                    printf("client epoll ctl error \n");
                    close(client_fd);
                    continue;
                }
            }
            else
            {
                //epoll client에 등록 된 클라이언트들의 send data 처리하기
                int32 str_len;
                int client_fd = _events[i].data.fd;
                char data[4096];
                str_len = read(client_fd,&data,sizeof(data));

                if(str_len==0)
                {
                    printf("client Disconnect [%d] \n",client_fd);
                    close(client_fd);
                    epoll_ctl(_fdEpoll,EPOLL_CTL_DEL,client_fd,nullptr);
                }
                else
                {
                    // TODO : Receiver 생성
                    printf("Recv Data [%d] \n",client_fd);
                }
            }
        }
    }

}

