#ifndef   MY_ALL_FILE_H 
#define   MY_ALL_FILE_H

#include "public_head.h"

struct sendfile
{
	int num;
	long pkgnum;
	char time[20];
	long time_l;
	char name[20];
	struct sendfile* next;
};

void FormatTime(time_t time1, char *szTime);

struct sendfile file_size2(char* filename);
//好友链表初始化
int init_S_file_List();

//添加用户
int add_S_file_List(long mid_pkgnum,char mid_name[],char mid_time[],long mid_time_l);

//获取当前目录的文件，并加入到链表中
void get_files();


void show_S_Flist();   


#endif
