#include "sendmsg.h"


//成功返回0,失败返回1
void send_msg(struct in_addr *FF_addr)
{
	//发送消息
	char mid_send_buf[BUFF_SIZE];
	char send_buf[BUFF_SIZE];
	printf("Please input message:");
	scanf("%s",mid_send_buf);
	//准备要发送的内容
	coding(send_buf,IPMSG_SENDMSG,mid_send_buf);
	get_time();
	//sprintf(send_buf,"1:%s:%s:%s:288:%s",time_str,My_name,My_mac,mid_send_buf);
	int send_Bt;
	//定义一个目标sockaddr并且初始化
	struct sockaddr_in F_sock_addr;
	memset(&F_sock_addr,0,sizeof(F_sock_addr));
	F_sock_addr.sin_family=AF_INET;
	F_sock_addr.sin_port=htons(MSG_PORT);
	F_sock_addr.sin_addr.s_addr=FF_addr->s_addr;
	//纪念一下5/24号下午用时三小时测试修改的bug
	//inet_pton(AF_INET,"10.18.54.244",&F_sock_addr.sin_addr.s_addr);/*设置对应ip*/
	//char mmm[30];
	//strcpy(mmm,inet_ntoa(F_sock_addr.sin_addr));
	//printf(">>>>>>>>>>>>>>> %s >>>>>>>>>>>>>>>\n",mmm);
	//修改成为选择的发送对象
	if((send_Bt=sendto(udp_fd,send_buf,strlen(send_buf),0,(struct sockaddr*)&F_sock_addr,sizeof(struct sockaddr)))< 0)
	{
		printf("sendto fail!!!\n");
	}
}
