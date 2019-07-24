#ifndef   FILELIST_H 
#define   FILELIST_H
#include "public_head.h"
//文件信息结构体
struct Recv_File
{
	struct in_addr sin_addr;//文件来源IP地址
	char name[50];//文件名
	long unsigned int num;// 文件序号
	int listnum;//列表中的号，唯一的，用于选择
	long pkgnum;//包编号
	long size;//文件大小
	long ltime;//最后修改时间
	//发送者用户名
	char user[20];
	struct Recv_File *next;
};

//初始化文件链表
int init_FileList();

//添加新的文件信息 添加完成返回0,错误返回1
int add_rcvFile(struct in_addr *sin_addr,char name[],long unsigned int num,long pkgnum,long size,char user[]);

//查找需要接收的文件
struct Recv_File* getFile(int file_id);

//从列表中删除已接收的文件信息
int del_rcvFile(int file_id);

//打印文件列表
void show_FileList();



#endif
