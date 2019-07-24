#ifndef   SENDMSG_H 
#define   SENDMSG_H
#include "public_head.h"
//向目标发送消息
//成功返回0,失败返回1
void send_msg(struct in_addr *FF_addr);
#endif
