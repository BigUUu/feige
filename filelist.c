#include "filelist.h"


//初始化文件链表
int init_FileList()
{
	fileHead = (struct Recv_File*)malloc(sizeof(struct Recv_File));
	if(fileHead ==NULL)
	{
		perror("don't malloc!!!");
		return 1;
	}
	memset(fileHead,0,sizeof(fileHead));
	fileHead->next = NULL;
	fileHead->listnum=0;
	return 0;
}

//添加新的文件信息 添加完成返回0,错误返回1
int add_rcvFile(struct in_addr *sin_addr,char name[],long unsigned int num,long pkgnum,long size,char user[])
{
	struct Recv_File *newFile=NULL;
	struct Recv_File *Pointer=fileHead;
	
		//申请内存空间
	if((newFile = (struct Recv_File*)malloc(sizeof(struct Recv_File)))==NULL)
	{
		printf("newFile failed!\n");
		return 1;
	}
	//将数据复制给新节点
	newFile->sin_addr.s_addr=sin_addr->s_addr;
	strcpy(newFile->name,name);
	newFile->num=num;
	newFile->pkgnum=pkgnum;
	newFile->size=size;
	strcpy(newFile->user,user);
	while(Pointer->next!=NULL)
	{
		Pointer=Pointer->next;
	}
	Pointer->next=newFile;
	newFile->next=NULL;
	return 0;
		
}


//查找需要接收的文件
struct Recv_File* getFile(int file_id)
{
	struct Recv_File *Pointer=fileHead;
	while((Pointer->next!=NULL)&&(Pointer->listnum!=file_id))
	{
		Pointer=Pointer->next;
	}
	if(Pointer->listnum==file_id)
		return Pointer;
	printf("not find the num\n");
	return NULL;
}


//从列表中删除已接收的文件信息
int del_rcvFile(int file_id)
{
	
	struct Recv_File *Pointer=fileHead;
	struct Recv_File *Pointer_1=fileHead->next;
	while((Pointer_1->listnum!=file_id)&&(Pointer_1->next!=NULL))
	{
		Pointer=Pointer_1;
		Pointer_1=Pointer_1->next;
	}
	if(Pointer_1->listnum==file_id)
	{
		Pointer->next=Pointer_1->next;
		free(Pointer_1);
		Pointer_1=NULL;
		return 1;
	}
	return 0;
}



//打印可接收文件列表
void show_FileList()
{
	struct Recv_File *midFile=fileHead->next;
	char F_ip[20];
	int mid_n=1;
	printf(" 		\033[1;31;46m当前可接收文件 \033[0m\n");
	printf("=============================================\n");
	printf("= num   文件名              From              =\n");
	while(midFile!=NULL)
	{
		midFile->listnum=mid_n;
		strcpy(F_ip,inet_ntoa(midFile->sin_addr));
		printf("= %-3d  %-18s %-20s(%20s)=\n",midFile->listnum,midFile->name,midFile->user,F_ip);
		midFile=midFile->next;
		mid_n++;
	}
	printf("=============================================\n");
	
}











