#include "public_head.h"

//全局变量-----------------------------------------
/*获取系统时间戳*/
char time_str[25];
/* udp_socket文件描述符 */ 
int udp_fd = 0;
/*tcp_socket文件描述符 */
int tcp_fd = 0;

//udp my_linux_addr
struct sockaddr_in udp_sock_addr;
//udp 数据来源的地址
struct sockaddr_in udp_recv_addr;
//tcp my_linux_addr
struct sockaddr_in tcp_sock_addr;
//tcp 数据来源的地址
struct sockaddr_in tcp_recv_addr;


//接受消息时的目标信息 
struct goal goal_person;
//接受的数据
char recvbuf[BUFF_SIZE]; 
//存储好友的链表
struct user *friends=NULL;

//存储文件的链表
struct Recv_File * fileHead=NULL;

//存储本地文件的链表
struct sendfile *S_file_header=NULL;

//----------个人信息-------------------------------
char My_name[20]="AAAAA";
char My_mac[50]="User's Mac";

int main()
{
	printf("Please enter user name:");
	scanf("%s",My_name);
	//初始化好友列表
	init_userList();
	//初始化文件列表
	init_FileList();
	//初始化本地文件列表
	init_S_file_List();
	pthread_t udp_rcv,key_scan;
	int ret=0;
	creat_socket();
	broadcast();
	ret=pthread_create(&udp_rcv,NULL,(void *)&udp_recv_pthread,NULL);
	if(ret!=0)
	{
		perror("pthread_create");
		exit(-1);
	}
	ret=pthread_create(&key_scan,NULL,(void *)&cmd_pthread,NULL);
	if(ret!=0)
	{
		perror("pthread_create");
		exit(-1);
	}
	for(int i=0;i<10000;++i)
	{
		for(int j=0;j<2000;++j);
	}
	show_userList();
	//pthread_join(udp_recv_pthread,NULL);
	while(1)
	{
	
	}
	return 0;
}










