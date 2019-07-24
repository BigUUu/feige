ipmsg:main.o get_time.o creat_socket.o broadcast.o udp_recv_pthread.o cmd_pthread.o pack_unpack.o udp_handle.o userlist.o outline.o sendmsg.o tcp_send_file.o filelist.o my_all_file.o
	gcc main.o get_time.o creat_socket.o broadcast.o udp_recv_pthread.o cmd_pthread.o pack_unpack.o udp_handle.o userlist.o outline.o sendmsg.o tcp_send_file.o filelist.o my_all_file.o -lpthread -o ipmsg
main.o:main.c
	gcc -c main.c -o main.o
get_time.o:get_time.c
	gcc -c get_time.c -o get_time.o
creat_socket.o:creat_socket.c
	gcc -c creat_socket.c -o creat_socket.o
broadcast.o:broadcast.c
	gcc -c broadcast.c -o broadcast.o
udp_recv_pthread.o:udp_recv_pthread.c
	gcc -c udp_recv_pthread.c -o udp_recv_pthread.o
cmd_pthread.o:cmd_pthread.c
	gcc -c cmd_pthread.c -o cmd_pthread.o
pack_unpack.o:pack_unpack.c
	gcc -c pack_unpack.c -o pack_unpack.o
udp_handle.o:udp_handle.c
	gcc -c udp_handle.c -o udp_handle.o
userlist.o:userlist.c
	gcc -c userlist.c -o userlist.o	
outline.o:outline.c
	gcc -c outline.c -o outline.o	
sendmsg.o:sendmsg.c
	gcc -c sendmsg.c -o sendmsg.o
tcp_send_file.o:tcp_send_file.c
	gcc -c tcp_send_file.c -o tcp_send_file.o	
filelist.o:filelist.c
	gcc -c filelist.c -o filelist.o		
my_all_file.o:my_all_file.c
	gcc -c my_all_file.c -o my_all_file.o	
