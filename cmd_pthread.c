#include "public_head.h"

//接收文件
void getfile_cmd()
{
	//打印可接收的文件的列表
	show_FileList();
	printf("please choose file ID:");
	int file_id=0;
	//输入需要接收的文件的num
	scanf("%d",&file_id);
	struct Recv_File *file=getFile(file_id);
	printf("=============================\n");
	char cmd_buf[1024];
	if(file == NULL)
	{
		printf("not find file\n");
		return;
	}
	FILE *fd;
	if((fd=fopen(file->name,"rb+"))==NULL)
	{
		int sockfd;
		int ren;
		struct sockaddr_in myaddr;
		//初始化
		myaddr.sin_family=AF_INET;
		myaddr.sin_port=htons(MSG_PORT);
		//通过文件列表获取文件名和文件ip
		//有点小问题
		char *server_ip = inet_ntoa(file->sin_addr);
		inet_pton(AF_INET,server_ip,&myaddr.sin_addr);
		//创建套接字
		sockfd = socket(AF_INET,SOCK_STREAM,0);
		//判断socket是否创建成功
		if(sockfd<0)
		{
			perror("socket");
			exit(-1);
		}
		char sendbuf[1024];
		printf("start connect tcp\n");
		//开始连接
		int tcp_len =0;
		tcp_len = connect(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr));
		if(tcp_len!=0)
		{
			perror("tcp connect error");
		}
		//此处可以使用memset清零
		bzero(cmd_buf,1024);
		char codingbuff[1024];
		int sendBytes;
		//这里可能有点小问题
		sprintf(cmd_buf,"%lx:%lx:%d",file->pkgnum,file->num,0);
		//附加信息打包
		printf("%s\n",cmd_buf);
		coding(codingbuff,IPMSG_GETFILEDATA,cmd_buf);
		//整体信息打包
		printf("%s\n",codingbuff);
		if((sendBytes = send(sockfd,codingbuff,strlen(codingbuff),0))==-1)
		{
			printf("tcp send fail\n");
			return;
		}
		if((fd=fopen(file->name,"wb+"))==NULL)
		{
			perror("open error");
			exit(-1);
		}
		else
		{
			char file_sendbuf[1024];
			//用于统计接收总长度
			int file_size=0;
			int recv_len=0;
			do
			{
				//每次都清空接受区域
				bzero(file_sendbuf,sizeof(file_sendbuf));
				recv_len = recv(sockfd,file_sendbuf,sizeof(file_sendbuf),0);
				file_size=file_size+recv_len;
				//将接收的数据写到本地文件中
				fwrite(file_sendbuf,sizeof(char),recv_len,fd);
				//显示已接收的数据量和数据总量
				printf("***size = %d *** file->size = %ld ***\n",file_size,file->size);
				
			
			}while(file_size<(file->size));
			//如果接收的数据量=要发送的数据总量，则发送成功
			if(file_size ==file->size)
			{
				printf("successfully receive file\n");
				del_rcvFile(file_id);
			}
			else
			{
				printf("can't receive file!!!'\n");
			}
			
			//del_rcvFile_name(file->name);
			fclose(fd);
			close(sockfd);
			return;
		}
		
		
		
	}
}

//发送文件
void sendfile_cmd(void *input_name)
{
	int ret=0;
	//存储目标信息
	struct goal cmd_obj;
	//连接套接字
	int con_sockt;
	FILE *fd;
	int recvbytes;
	int len;
	//这是文件的结构体
	//struct sendfile sendfiles;
	//struct sendfile *send_files;
	char recvbuf[BUFF_SIZE];
	
	len=sizeof(tcp_sock_addr);
	ret=listen(tcp_fd,30);
	if(ret!=0)
	{
		perror("listen");
		exit(-1);
	}
	
	//while(1)
	//{
		con_sockt=accept(tcp_fd,(struct sockaddr*)&tcp_sock_addr,&len);
		printf("TCP连接成功\n");
		recvbytes=recv(con_sockt,recvbuf,sizeof(recvbuf),0);
		recvbuf[recvbytes]='\0';
		printf("接收到的包:%s",recvbuf);
		memset(&cmd_obj,0,sizeof(struct goal));
		transcode(&cmd_obj,recvbuf,recvbytes);
		printf("解析的包为：%s\n",cmd_obj.name);
		if(GET_MODE(cmd_obj.id_key)==IPMSG_GETFILEDATA)
		{
			long pkpk=120;
			int numnum=1;
			//sscanf(cmd_obj.last_msg,"%lx:%d",&sendfiles.pkgnum,&sendfiles.num);
			sscanf(cmd_obj.last_msg,"%lx:%d",&pkpk,&numnum);
			//看看是否接收到对面确认接受的信息
			printf("====hello hello hello====\n");
			//这个函数===============
			//send_files=get_sendFile_num(sendfile.num);
			//测试
			//fd=fopen(send_files->name,"rb+");
			
			fd=fopen((char*)input_name,"rb+");
			if(fd==NULL)
			{
				//在当前路径没有找到该文件
				printf("File:%s not found in current path\n",(char*)input_name);
				return;
			}
			//文件发送缓冲区
			char sendbuf_file[BUFF_SIZE];
			bzero(sendbuf_file,BUFF_SIZE); 
			
			int file_block_length=0;
			//
			while((file_block_length=fread(sendbuf_file,sizeof(char), BUFF_SIZE,fd))>0)
			{
				printf("%d\n",file_block_length);
				if(write(con_sockt,sendbuf_file,file_block_length)<0)
				{
					perror("send!!!");
					return;
				}
				//发送一次数据后把缓冲区清零
				bzero(sendbuf_file,BUFF_SIZE);
			}
			
			//这个函数======
			//del_sendFile_name(send_files->name);
			fclose(fd);
			printf("Transfer file finished \n");
			close(con_sockt);
			
		}
	//}
}


//获取输入的指令
void cmd_pthread()
{
	char buf[30];
	int recvBytes;
	while(1)
	{
		memset(&buf,0,sizeof(buf));
		//读取键盘输入
		if((recvBytes=read(STDIN_FILENO,buf,sizeof(buf)))!=-1)
		{
			//C语言字符串结尾必须是\0
			buf[recvBytes-1]='\0';
			//下面是对获取的指令进行处理
			if(strncmp(buf,"send",4)==0)
			{
				printf("sendto_cmd\n");
				//打印一下好友列表
				show_userList();
				int F_d=0;
				
				printf("Please choose the target(enter num):\n");
				scanf("%d",&F_d);
				//对输入的数据进行处理
				//if(F_d<1||F_d>)
				//将字符串转换成int类型
				//F_d=atoi(&buf[7]);
				struct in_addr F_addr;//目标IP地址
				struct user *F_user=friends->next;
				//从朋友列表中找到目标信息
				while(F_user!=NULL)
				{
					if(F_user->num==F_d)
					{
						F_addr=F_user->sin_addr;
						break;
					}
					F_user=F_user->next;
				}
				//发送信息
				send_msg(&F_addr);
			}
			
			else if(strncmp(buf,"lsfile",6)==0)
			{
				//打印可接收的文件的列表
				show_FileList();
			}
			//确定接收文件
			else if(strncmp(buf,"getfile",7)==0)
			{
				//接受文件
				getfile_cmd();
			}
			else if(strncmp(buf,"sdfile",8)==0)
			{
				//先通过UDP给对面发送一条我要发送文件的消息
				//打印一下好友列表
				show_userList();
				int F_d=0;
				printf("请选择发送给谁(enter num)：");
				//printf("Please choose the target(enter num):\n");
				scanf("%d",&F_d);
				//对输入的数据进行处理
				//if(F_d<1||F_d>)
				//将字符串转换成int类型
				//F_d=atoi(&buf[7]);
				struct in_addr F_addr;//目标IP地址
				struct user *F_user=friends->next;
				//从朋友列表中找到目标信息
				while(F_user!=NULL)
				{
					if(F_user->num==F_d)
					{
						F_addr=F_user->sin_addr;
						break;
					}
					F_user=F_user->next;
				}
				
				//获取到对面ip F_addr
				char mid_file_msg[BUFF_SIZE];
				
				//获取要发送的文件
				get_files();
				show_S_Flist();
				printf("请选择要发送的文件：");
				scanf("%d",&F_d);
				//从列表中查找需要发送的文件
				struct sendfile *F_file=S_file_header->next;
				//从朋友列表中找到目标信息
				while(F_file!=NULL)
				{
					if(F_file->num==F_d)
					{
						break;
					}
					F_file=F_file->next;
				}
				//如果追求严谨，此处应该判断是否找到
				
				
				get_time();
				//组装信息，告诉对面，我要发送文件了
				//UDP
				int mid_flag=IPMSG_SENDMSG|IPMSG_FILEATTACHOPT|IPMSG_SENDCHECKOPT;
				char mid_add_msg[200];
				//sprintf(mid_add_msg,".0:%s:%s:%lx:0:1",time_str-1,F_file->name,F_file->pkgnum);
				//char S_mid_pkgnum[20];
				//sprintf(S_mid_pkgnum,"%x",F_file->pkgnum);
				sprintf(mid_add_msg,".0:%s:%lx:%lx:%ld:",F_file->name,F_file->pkgnum,F_file->time_l,IPMSG_FILE_REGULAR);
				sprintf(mid_file_msg,"1:%s:%s:%s:%d:%s",time_str,My_name,My_mac,mid_flag,mid_add_msg);
				//printf("%s++++++++++++++\n",mid_file_msg);
				struct sockaddr_in mid_F_sock_addr;
				memset(&mid_F_sock_addr,0,sizeof(mid_F_sock_addr));
				mid_F_sock_addr.sin_family=AF_INET;
				mid_F_sock_addr.sin_port=htons(MSG_PORT);
				mid_F_sock_addr.sin_addr.s_addr=F_addr.s_addr;
				int mid_send_Bt;
				if((mid_send_Bt=sendto(udp_fd,mid_file_msg,strlen(mid_file_msg),0,(struct sockaddr*)&mid_F_sock_addr,sizeof(struct sockaddr)))< 0)
				{
					printf("sendto fail!!!\n");
				}
				//发送文件
				
				//开一个线程
				pthread_t send_thread;
				pthread_create(&send_thread,NULL,(void*)sendfile_cmd,F_file->name);
				//sendfile_cmd(F_file->name);
				
			}
			else if(strncmp(buf,"ls",2)==0)
			{
				printf("ls_cmd\n");
				show_userList();
			}
			else if(strncmp(buf,"help",4)==0)
			{
				printf("help_cmd\n");
				printf("***********************************\n");
				printf("*1.send      发送信息             *\n");
				printf("*2.ls        打印好友列表         *\n");
				printf("*3.lsfile    打印可接受的文件列表 *\n");
				printf("*4.getfile   接收文件             *\n");
				printf("*5.sdfile    发送文件             *\n");
				printf("*6.exit      下线                 *\n");
				printf("***********************************\n");
				//help_cmd();
			}
			else if(strncmp(buf,"exit",4)==0)
			{
				printf("ByeBye\n");
				outline();
				exit(-1);
			}
		}
	}
}
