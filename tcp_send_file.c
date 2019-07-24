#include "tcp_send_file.h"

void *tcp_send_file()
{
	int recvbytes;
	char tcp_recv_buf[1024];
	
	//定义一个目标节点
	struct goal cmd_obj;
	//连接套接字
	int con_sockt;
	//获取用于存放目的信息的地址的长度
	int addrlen=sizeof(tcp_recv_addr);
	//创建监听
	int ret=listen(tcp_fd,30);
	//判断监听是否成功
	if(ret!=0)
	{
		perror("listen");
		exit(-1);
	}
	
	while(1)
	{
		//printf("等待TCP连接\n");
		con_sockt = accept(tcp_fd,(struct sockaddr*)&tcp_recv_addr,&addrlen);
		printf("TCP connect success\n");
		//接受对面需要getfile的信息
		recvbytes = recv(con_sockt,tcp_recv_buf,sizeof(tcp_recv_buf),0);
		tcp_recv_buf[recvbytes]='\0';
		printf("%s\n",tcp_recv_buf);
		//清空目标信息，用于重新解析接收
		memset(&cmd_obj,0,sizeof(cmd_obj));
		//解析信息
		transcode(&cmd_obj,tcp_recv_buf,recvbytes);
		if(GET_MODE(cmd_obj.id_key)==IPMSG_GETFILEDATA)
		{
			printf("hello hello hello\n");
		}
		
	}
		
		
	
}
