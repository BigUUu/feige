#include "my_all_file.h"


void FormatTime(time_t time1, char *szTime)  
{  
    struct tm tm1;  
#ifdef WIN32  
    tm1 = *localtime(&time1);  
#else  
    localtime_r(&time1, &tm1 );  
#endif  
    sprintf( szTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d",  
           tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday,  
             tm1.tm_hour, tm1.tm_min,tm1.tm_sec);  
} 


//获取每个文件属性
struct sendfile file_size2(char* filename) 
{ 
 	struct stat statbuf; 
 	struct sendfile mid_sendfile;
  	stat(filename,&statbuf); 
  	mid_sendfile.pkgnum=statbuf.st_size; 
  	//printf("%s\n",(char*)statbuf.st_ctime);
  	mid_sendfile.time_l=statbuf.st_ctime;
  	FormatTime(statbuf.st_ctime,mid_sendfile.time);
  	//printf("============================\n");
  	//printf("time=%s\n",mid_sendfile.time);
  	//printf("size=%ld\n",mid_sendfile.pkgnum);
  	//printf("============================\n");
  	return mid_sendfile; 
}


//好友链表初始化
int init_S_file_List()
{
	S_file_header = (struct sendfile*)malloc(sizeof(struct sendfile));
	if(S_file_header ==NULL)
	{
		perror("don't malloc!!!");
		return 1;
	}
	//memset(S_file_header,0,sizeof(struct S_file_header));
	return 0;
}


//添加用户
int add_S_file_List(long mid_pkgnum,char mid_name[],char mid_time[],long mid_time_l)
{
	//定义一个节点
	struct sendfile *new_S_file=NULL;
	struct sendfile *rear_file = S_file_header;
	//申请内存空间
	if((new_S_file = (struct sendfile*)malloc(sizeof(struct sendfile)))==NULL)
	{
		printf("new_S_file failed!\n");
		return 1;
	}
	new_S_file->pkgnum=mid_pkgnum;
	new_S_file->time_l=mid_time_l;
	strncpy(new_S_file->name,mid_name,20);
	strncpy(new_S_file->time,mid_time,20);
	
	//找到链表末尾
	while(rear_file->next!=NULL)
	{
		rear_file =rear_file->next;
	}
	rear_file->next = new_S_file;
	new_S_file->next =NULL;
	return 0;

}


//获取当前目录的文件，并加入到链表中
void get_files()
{
    DIR *dirp; 
    struct dirent *dp;
    struct sendfile my_sendfile;
    dirp = opendir("."); //打开目录指针
    while ((dp = readdir(dirp)) != NULL) 
    { //通过目录指针读目录
        my_sendfile=file_size2(dp->d_name);
        int ret=add_S_file_List(my_sendfile.pkgnum,dp->d_name,my_sendfile.time,my_sendfile.time_l);
        if(ret)
        {
        	printf("add_file_list error!!!\n");
        	return;
        }
        //printf("---------------------------------\n");
        //printf("%s\n", dp->d_name );
        //printf("%s\n",my_sendfile.time);
        //printf("%ld\n",my_sendfile.pkgnum);
        //printf("---------------------------------\n");
    }
    (void) closedir(dirp); //关闭目录
}


void show_S_Flist()
{
	struct sendfile *midFile=S_file_header->next;
	int mid_n=1;
	printf(" 		\033[1;31;46m当前目录的文件 \033[0m\n");
	printf("=======================================================\n");
	printf("= num   文件名           大小           时间          =\n");
	while(midFile!=NULL)
	{
		midFile->num=mid_n;
		printf("= %-3d  %-16s %-10ld %18s =\n",midFile->num,midFile->name,midFile->pkgnum,midFile->time);
		midFile=midFile->next;
		mid_n++;
	}
	printf("=======================================================\n");
	
}

