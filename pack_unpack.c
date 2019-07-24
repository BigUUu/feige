#include "pack_unpack.h"

//将接收到的字符串分解为struct cmd结构体
void transcode(struct goal *mid,char *mid_buffer,int len)
{
	//解析字符串，以:为界，全部分割
	char mid_key[50];
	sscanf(mid_buffer,"%[^:]:%[^:]:%[^:]:%[^:]:%d:%[^\n]",mid_key,mid->time_num,mid->name,mid->macnum,&mid->id_key,mid->last_msg);
	//printf("%d\n",mid->id_key);
	//printf("%s\n",mid->name);
	//printf("%s\n",mid->macnum);
	//printf("%s\n",mid->last_msg);
}

//要发送的信息编码为字符串保存在buf中
void coding(char *mid_buffer,unsigned int mid_num,char *append)
{
	//获取系统时间戳，保证这个值是唯一的
	get_time();
	sprintf(mid_buffer,"1:%s:%s:%s:%d:%s",time_str,My_name,My_mac,mid_num,append);
}



