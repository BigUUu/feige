#include "outline.h"

void outline(void)
{
	struct sockaddr_in out_cast_addr;
	char outline_msg[1024];
	int outBytes;
	int outset=1;
	if(setsockopt(udp_fd, SOL_SOCKET, SO_BROADCAST, &outset, sizeof(outset))< 0)
	{
		printf("setsockopt failed!");
		exit(-1);
	}
	memset(&out_cast_addr,0,sizeof(out_cast_addr));
	out_cast_addr.sin_family=AF_INET;
	out_cast_addr.sin_port=htons(MSG_PORT);
	inet_pton(AF_INET,"255.255.255.255",&out_cast_addr.sin_addr.s_addr);/*设置ip*/
	get_time();
	sprintf(outline_msg,"1:%s:%s:%s:2:%s",time_str,My_name,My_mac,My_name);
	/*广播发送上线通知*/
	if(outBytes = sendto(udp_fd, outline_msg , strlen(outline_msg), 0 ,(struct sockaddr*) &out_cast_addr, sizeof(out_cast_addr))<0)
	{
		printf("outline fail\r\n");
		exit(-1);
	}
}
