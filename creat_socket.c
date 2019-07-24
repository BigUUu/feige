#include "creat_socket.h"

void creat_socket(void)
{
	//创建socket套接字
	if((udp_fd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("create udp_socket error\n");
		exit(-1);
	}
	if((tcp_fd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("create tcp_socket error\n");
		exit(-1);
	}
	
	int set=1;
	//setsockopt用于配置socket套接字
	if(setsockopt(udp_fd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set))< 0)
	{
		printf("setsockopt failed!");
		exit(-1);
	}
	
	//udp初始化
	memset(&udp_sock_addr,0,sizeof(struct sockaddr_in));
	udp_sock_addr.sin_family = AF_INET;
	udp_sock_addr.sin_port = htons(MSG_PORT);
	udp_sock_addr.sin_addr.s_addr = INADDR_ANY;
	
	//tcp初始化
	memset(&tcp_sock_addr,0,sizeof(struct sockaddr_in));
	tcp_sock_addr.sin_family = AF_INET;
	tcp_sock_addr.sin_port = htons(MSG_PORT);
	tcp_sock_addr.sin_addr.s_addr = INADDR_ANY;
		
	//bind
	//绑定目的是限制进程创建的socket只接受那些目的为此ip的客户链接
	if(bind(udp_fd,(struct sockaddr *)&udp_sock_addr,sizeof(udp_sock_addr))<0)
	{
		printf("bind error :\r\n");
		exit(-1);
	} 
	
	
	//绑定目的是限制了服务端进程创建的socket直接受那些目的地为此IP地址的客户链接
	if(bind(tcp_fd,(struct sockaddr *)&tcp_sock_addr,sizeof(tcp_sock_addr))<0)
	{
		printf("bind error :\r\n");
		exit(-1);
	}
	
}
