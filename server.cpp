#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <string.h>
#include <stdio.h>

#define PORT_NUM 3600
#define EPOLL_SIZE 100
#define MAXLINE 1024

struct udata
{
	int fd;
	char name[80];
};

int user_fds[1024];

void send_msg(struct epoll_event ev,char* msg);

int main(int argc,char **argv)
{
	struct sockaddr_in addr,clientaddr;
	struct epoll_event ev, *events;
	struct udata *user_data;

	int listenfd;
	int clientfd;
	int i;
	socklen_t addrlen,clilen;
	int readn;
	int eventn;
	int epollfd;
	char buf[MAXLINE];

	events = (struct epoll_event *)malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	if((epollfd = epoll_create(100))==-1)
		return -1;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NUM);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listenfd,(struct sockaddr *)&addr,addrlen)==-1)
		return 1;


	listen(listenfd,5);

	ev.events = EPOLLIN;
	ev.data.fd = listenfd;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev);
	memset(user_fds,-1,sizeof(int)*1024);

	while(1)
	{
		eventn = epoll_wait(epollfd,events,EPOLL_SIZE,-1);
		if(eventn==-1)
		{
			return 1;
		}
		for(i=0;i<eventn;i++)
		{
			if(events[i].data.fd == listenfd)
			{
				memset(buf,0x00,MAXLINE);
				clilen = sizeof(struct sockaddr);
				clientfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);
				user_fds[clientfd]=1;

				user_data = malloc(sizeof(user_data));
				user_data->fd = clientfd;

				char* tmp = "First insert yout nickname : ";
				write(user_data->fd,tmp,29);

				sleep(1);
				read(user_data->fd,user_data->name,sizeof(user_data->name));
				user_data->name[strlen(user_data->name)-1]=0;

				printf("Welcome [%s] \n" user_data->name);

				sleep(1);
				sprintf(buf,"Okay your nickname : %s \n",user_data->name);

				write(user_data->fd,buf,40);

				ev.events = EPOLLIN;
				ev.data.ptr = user_data;

				epoll_ctl(epollfd,EPOLL_CTL_ADD,clientfd,&ev);
			}
			else
			{
				user_data = events[i].data.ptr;
				memset(buf,0x00,MAXLINE);
				readn = read(user_data->fd,buf,MAXLINE);
				if(readn <=0)
				{
					epoll_ctl(epollfd,EPOLL_CTL_DEL,user_data->fd,events);
					close(user_data->fd);
					user_fds[user_data->fd]=-1;
					free(user_data);
				}
				else
				{
					send_msg(events[i],buf);
				}
			}
		}
	}
}

void send_msg(struct epoll_event ev,char* msg)
{
	int i;
	char buf[MAXLINE+24];
	struct udata *user_data;
	for(i=0;i<1024;i++)
	{
		memset(buf,0x00,MAXLINE+24);
		sprintf(buf,"%s : %s",user_data->name,msg);
		if((user_fds[i]==1))
		{
			write(i,buf,MAXLINE+24);
		}
	}
}


