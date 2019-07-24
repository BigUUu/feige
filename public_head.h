#ifndef   PUBLIC_HEAD_H 
#define   PUBLIC_HEAD_H
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <pthread.h>
#include <sys/time.h> 
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h> 
#include <time.h>

//包含的自定义函数包
#include "IPMSG.h"
#include "get_time.h"
#include "creat_socket.h"
#include "broadcast.h"
#include "pack_unpack.h"
#include "udp_handle.h"
#include "userlist.h"
#include "outline.h"
#include "sendmsg.h"
#include "filelist.h"
#include "my_all_file.h"


#define MSG_PORT 2425
#define FROM_PORT 2425
#define BUFF_SIZE 1024

//-----函数声明----------------
//接受信息
void udp_recv_pthread(void);
//获取输入的指令
void cmd_pthread();

//-----自定义结构体-------------
//定义接收到的信息
struct Data_Ipmsg{
	int  version_id;
	char package_no[11];
	char user[10];
	char machine[50];
	int  commend;
	char add_msg[100];
	char ip_addr[20];
};

/*
//定义接受到的文件
struct Recv_File{
	struct in_addr sin_addr;//文件来源IP地址
	long unsigned int num;
	char name[50];
	long unsigned int size;
};
*/
//-----全局变量----------------
/*获取系统时间戳*/
extern char time_str[25];
/* socket文件描述符 */ 
extern int udp_fd;

/* socket文件描述符 */ 
extern int tcp_fd;


//udp my_linux_addr
extern struct sockaddr_in udp_sock_addr;
//udp 数据来源的地址
extern struct sockaddr_in udp_recv_addr;
//tcp my_linux_addr
extern struct sockaddr_in tcp_sock_addr;
//tcp 数据来源的地址
extern struct sockaddr_in tcp_recv_addr;

//接受消息时的目标信息
extern struct goal goal_person;
//接受的数据
extern char recvbuf[BUFF_SIZE]; 
//存储好友的链表
extern struct user *friends;
//存储文件的链表
extern struct Recv_File * fileHead;
//存储文件的链表
extern struct sendfile *S_file_header;

//临时文件信息
extern struct Recv_File rcvfiles;

//------个人信息-------------------
extern char My_name[20];
extern char My_mac[50];


struct Data_Ipmsg msg;

socklen_t iAddrLength; 
//struct sockaddr_in to_addr;  //airing_pc_addr
//struct sockaddr_in src_addr; //one_person_addr

#endif
