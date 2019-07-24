#include "udp_handle.h"

struct Recv_File rcvfiles;

void udp_recv_handle(struct goal *mid,struct sockaddr_in* send_addr)
{
	unsigned long tmp=0;
	char send_ip[20];
	strcpy(send_ip,inet_ntoa(send_addr->sin_addr));
	//接收到用户广播上线的信息
	//GET_MODE包含在IPMSG.h的头文件中，是一种特殊的计算方式
	//if(mid->id_key==1)
	if((GET_MODE(mid->id_key)==IPMSG_BR_ENTRY))
	{
		//判断有没有此用户
		//根据sin_addr判断，因为ip是唯一的
		if(!getUser(send_addr->sin_addr))
		{
			if(addUser(send_addr->sin_addr,mid->name,mid->macnum))
			{
				printf("addUser error!!!\n");
			}
			//printf(" \033[1;31;46m当前在线 \033[0m\n");
			printf("\033[1;37;42m<<<<<<<<%s : %s  上线了！！！>>>>>>>>>>\033[0m\n",mid->name,send_ip);
			//printf("<<<<<<<<%s : %s  上线了！！！>>>>>>>>>>\n",mid->name,send_ip);
		}
		char midbuffer[BUFF_SIZE];
		memset(midbuffer,0,sizeof(midbuffer));
		//发送IPMSG_ANSENTRY信息
		coding(midbuffer,IPMSG_ANSENTRY,My_name);
		int sendBytes;
		if((sendBytes=sendto(udp_fd,midbuffer,strlen(midbuffer),0,(struct sockaddr*)send_addr,sizeof(struct sockaddr)))==-1)
		{
			printf("sendto fail!!!\n");
		}
		//回复一个3
	}
	//对面刷新好友列表
	//printf("%d====================\n",mid->id_key);
	//if(mid->id_key==0)
	if((GET_MODE(mid->id_key)==1025))
	{
		//判断有没有此用户
		//根据sin_addr判断，因为ip是唯一的
		if(!getUser(send_addr->sin_addr))
		{
			if(addUser(send_addr->sin_addr,mid->name,mid->macnum))
			{
				printf("addUser error!!!\n");
			}
		}
		//发送IPMSG_ANSENTRY信息
		char midbuffer[BUFF_SIZE];
		memset(midbuffer,0,sizeof(midbuffer));
		//发送IPMSG_ANSENTRY信息
		coding(midbuffer,IPMSG_ANSENTRY,My_name);
		int sendBytes;
		if((sendBytes=sendto(udp_fd,midbuffer,strlen(midbuffer),0,(struct sockaddr*)send_addr,sizeof(struct sockaddr)))==-1)
		{
			printf("sendto fail!!!\n");
		}
	}
	//接收到应答上线信息
	if((GET_MODE(mid->id_key)==IPMSG_ANSENTRY))
	{
		//判断有没有此用户
		//根据sin_addr判断，因为ip是唯一的
		if(!getUser(send_addr->sin_addr))
		{
			if(addUser(send_addr->sin_addr,mid->name,mid->macnum))
			{
				printf("addUser error!!!\n");
			}
		}
	}
	
	//接收到用户下线信息
	if((GET_MODE(mid->id_key)==IPMSG_BR_EXIT))
	{
		if(getUser(send_addr->sin_addr))
		{
			//判断是否删除成功
			if(delUser(send_addr->sin_addr))
			{
				//printf("=========================\n");
				printf("\033[1;37;45m<<<<<<<<%s : %s  outline！! ！>>>>>>>>>>\033[0m\n",mid->name,send_ip);
			}
		}
	}
	//接收到聊天信息
	if((GET_MODE(mid->id_key)==IPMSG_SENDMSG)&&((mid->id_key & IPMSG_FILEATTACHOPT)!=IPMSG_FILEATTACHOPT))	
	{
		printf("\033[1;31;40m%s : %s  \033[0m\n",mid->name,mid->last_msg);
		//发送收到消息的确认信息
		char midbuffer[BUFF_SIZE];
		memset(midbuffer,0,sizeof(midbuffer));
		coding(midbuffer,IPMSG_RECVMSG,mid->time_num);
		int sendBytes;
		if((sendBytes=sendto(udp_fd,midbuffer,strlen(midbuffer),0,(struct sockaddr*)send_addr,sizeof(struct sockaddr)))==-1)
		{
			printf("sendto fail!!!\n");
		}
	}
	
	//接收到文件
	if((GET_MODE(mid->id_key)==IPMSG_SENDMSG)&&((mid->id_key & IPMSG_FILEATTACHOPT)==IPMSG_FILEATTACHOPT))
	{
	
		//printf("\033[1;31;40m%s : file file file \033[0m\n",mid->name);
		//发送收到消息的确认信息
		char midbuffer[BUFF_SIZE];
		memset(midbuffer,0,sizeof(midbuffer));
		coding(midbuffer,IPMSG_RECVMSG,mid->time_num);
		int sendBytes;
		if((sendBytes=sendto(udp_fd,midbuffer,strlen(midbuffer),0,(struct sockaddr*)send_addr,sizeof(struct sockaddr)))==-1)
		{
			printf("sendto fail!!!\n");
		}
		//struct Recv_File rcvfiles;
		memset(&rcvfiles,0,sizeof(rcvfiles));
		//获取目标地址
		rcvfiles.sin_addr = send_addr->sin_addr;
		//获取包编号并转换
		rcvfiles.pkgnum=atol(mid->time_num);
		//获取发送者用户名
		strcpy(rcvfiles.name,mid->name);
		//最后修改时间
		//最后修改时间
		//最后修改时间
		
		char *p1=NULL;
		char *p2=NULL;
		char i;
		char *pp=NULL;
		p1 = strrchr(recvbuf,0);
		printf("接收到包含文件信息的UDP数据包：%s \n",recvbuf);
		printf("接收到的数据包解析：%s\n",p1);
		p2=(p1+1);
		printf("接收到的数据包再解析：%s\n",p2);
		//调试，检查一下包号是不是匹配
		printf("%ld\n----------",rcvfiles.pkgnum);
		sscanf(p2,"%lx:%[^:]:%lx",&rcvfiles.num,rcvfiles.name,&rcvfiles.size);
		pp = strtok(p2,":");
		for(i=0;i<strlen(pp);++i)
		{
			tmp = tmp*10 + (*p2 - 0x30);
			p2++;
		}
		rcvfiles.num=tmp;
		//有文件消息提示
		printf("\033[1;31;40m%s :(%s) file file file \033[0m\n",mid->name,inet_ntoa(send_addr->sin_addr));
		//输出文件名字
		printf("%s\n",rcvfiles.name);
		//把文件添加到文件列表中
		//add_rcvFile(&rcvfiles.sin_addr,rcvfiles.name,rcvfiles.num,rcvfiles.size);
		int add_ret;
		add_ret=add_rcvFile(&rcvfiles.sin_addr,rcvfiles.name,rcvfiles.num,rcvfiles.pkgnum,rcvfiles.size,rcvfiles.user);
		//判断是否添加成功
		if(add_ret)
		{
			printf("add_rcvFile error!!!\n");
		}
		
		
		
		
	}
	
	//对面取消文件发送
	if((GET_MODE(mid->id_key))==232)
	{
		struct Recv_File *Pointer=fileHead->next;
		while(Pointer!=NULL)
		{
			char mid_pk[30];
			sprintf(mid_pk, "%ld%ld", Pointer->pkgnum,Pointer->num);
			//打印一下附加信息
			//printf("%s\n",mid_pk);
			if(strncmp(mid->last_msg,mid_pk,strlen(mid_pk))==0)
			{
				printf("\033[1;31;40m%s :cancel send file \033[0m\n",mid->name);
				int del_ret=del_rcvFile(Pointer->listnum);
				break;
			}
			Pointer=Pointer->next;
		}
	}
	
	
	
	
	
	
		
	
}
