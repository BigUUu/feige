#include "broadcast.h"

//发送上线广播
void broadcast(void)
{
	struct sockaddr_in broad_cast_addr;
	//发送的字节
	int sendBytes;
	//msg储存发送的内容
	char buffer_msg[1024];
	
	//设置套接字类型，SO_BROADCAST为可接受和发送广播模式
	int set=1;
	if(setsockopt(udp_fd, SOL_SOCKET, SO_BROADCAST, &set, sizeof(set))< 0)
	{
		printf("setsockopt failed!");
		exit(-1);
	}
	memset(&broad_cast_addr,0,sizeof(broad_cast_addr));
	broad_cast_addr.sin_family=AF_INET;
	broad_cast_addr.sin_port=htons(MSG_PORT);
	inet_pton(AF_INET,"255.255.255.255",&broad_cast_addr.sin_addr.s_addr);/*设置ip*/
	//用户上线，打包，广播
	//lis_sock中包含本机IP，通过broad_cast_addr确定发送的方式
	get_time();
	sprintf(buffer_msg,"1:%s:%s:%s:1:%s",time_str,My_name,My_mac,My_name);
	
	/*广播发送上线通知*/
	if(sendBytes = sendto(udp_fd, buffer_msg , strlen(buffer_msg), 0 ,(struct sockaddr*) &broad_cast_addr, sizeof(broad_cast_addr))<0)
	{
		printf("broadcast fail\r\n");
		exit(-1);
	}
	
}
