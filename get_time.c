#include "get_time.h"

//获取系统时间戳，用于发送信息
void get_time()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	sprintf(time_str, "%ld", tv.tv_sec);
}

