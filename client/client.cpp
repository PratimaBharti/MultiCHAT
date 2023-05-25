#include "myheader.h"

int main(int argc,char *argv[])
{
	string ID = argv[1];
	int sock_fd = registerID(argv[1]);

	//threads created for sending and receiving simultaneously.
	thread th_send(send_text,sock_fd,ID.c_str());
	thread th_recv(recv_text,sock_fd);

	th_send.join();
	th_recv.join();
	
	return 0;

}
