#include "public_head.h"

void udp_recv_pthread(void)
{
	int recvbytes;
	//发送者的ip
	char ip_addr[20];
	int addrlen=sizeof(udp_recv_addr);
	memset(&udp_recv_addr,0,sizeof(struct sockaddr_in));
	while(1)
	{
		if(recvbytes=recvfrom(udp_fd, recvbuf , sizeof(recvbuf), 0 ,(struct sockaddr*) &udp_recv_addr, &addrlen)==-1)
		{
			printf("recv failed!\n");
		}
		else
		{
			//recvbuf[recvbytes]='\0';
			memset(&goal_person,0,sizeof(struct goal));
			//printf("正在解析------------------\n");
			transcode(&goal_person,recvbuf,recvbytes);
			udp_recv_handle(&goal_person,&udp_recv_addr);
			//printf("OK-------------------------\n");
			//此处调试用了老子2小时，真是个锤子
			//strcpy(ip_addr,inet_ntoa(udp_recv_addr.sin_addr));
			//此处调试时可以取消注释，显示所有收到的信息
			//printf ("发送者ip地址为：%s\n",ip_addr);
			//printf ("接受到数据buf=%s\r\n",recvbuf);
			//msg_handle(buf,ip_addr);
			memset(recvbuf,0,sizeof(recvbuf));
			//还应该清除一下udp_recv_addr
		
		}

	}
}

