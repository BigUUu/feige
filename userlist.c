#include "userlist.h"

//好友链表初始化
int init_userList()
{
	friends = (struct user*)malloc(sizeof(struct user));
	if(friends ==NULL)
	{
		perror("don't malloc!!!");
		return 1;
	}
	memset(friends,0,sizeof(struct user));
	//friends->next = NULL;
	return 0;
}


//添加用户
int addUser(struct in_addr sin_addr,char name[],char hostname[])
{
	//定义一个新用户节点
	struct user *newUser =NULL;
	struct user *rear = friends;
	//申请内存空间
	if((newUser = (struct user*)malloc(sizeof(struct user)))==NULL)
	{
		printf("newUser failed!\n");
		return 1;
	}
	//用户随机号
	newUser->sin_addr.s_addr = sin_addr.s_addr;
	strncpy(newUser->name,name,20);
	strncpy(newUser->host,hostname,20);
	
	//找到链表末尾
	while(rear->next!=NULL)
	{
		rear =rear->next;
	}
	rear->next = newUser;
	newUser->next =NULL;
	return 0;

}

//根据sin_addr 删除用户 正确删除返回0 错误返回1
int delUser(struct in_addr sin_addr)
{
	struct user *pre=NULL;
	struct user *suc=friends;
	while(suc->sin_addr.s_addr!=sin_addr.s_addr&&suc->next!=NULL)
	{
		pre=suc;
		suc=suc->next;
	}
	if(suc->sin_addr.s_addr==sin_addr.s_addr)
	{
		pre->next=suc->next;
		free(suc);
		return 1;
	}
	return 0;
}

//根据sin_addr 获取user结构体 没有返回NULL
//根据ip查找用户
struct user* getUser(struct in_addr sin_addr)
{
	struct user *cur;
	cur = friends;
	while(cur->sin_addr.s_addr!=sin_addr.s_addr&&cur->next!=NULL)
	{
		cur=cur->next;
	}
	if(cur->sin_addr.s_addr==sin_addr.s_addr)
	{
		return cur;
	}
	return NULL;
}

//打印好友列表
void show_userList()
{
	struct user *midF=friends->next;
	char F_ip[20];
	int mid_n=1;
	printf(" 		\033[1;31;46m当前在线 \033[0m\n");
	printf("=============================================\n");
	printf("= num   用户名              IP              =\n");
	while(midF!=NULL)
	{
		midF->num=mid_n;
		strcpy(F_ip,inet_ntoa(midF->sin_addr));
		printf("= %-3d  %-18s %-18s=\n",midF->num,midF->name,F_ip);
		midF=midF->next;
		mid_n++;
	}
	printf("=============================================\n");
	
} 









