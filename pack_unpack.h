#ifndef   PACK_UNPACK_H 
#define   PACK_UNPACK_H

//接受消息时的目标信息
struct goal{
	char time_num[30];
	char name[20];
	char macnum[50];
	int id_key;
	char last_msg[1024];

};

#include "public_head.h"

//将接收到的字符串分解为struct cmd结构体
void transcode(struct goal *mid,char *mid_buffer,int len);
//要发送的信息编码为字符串保存在buf中
void coding(char *mid_buffer,unsigned int mid_num,char *append);

#endif
