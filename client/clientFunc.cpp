#include "myheader.h"

//function which registers the user first time
int registerID(const char* id)
{
	struct message msg;
	const char *IP = serverIP;
	char buff[BUF_SIZE];
	socklen_t len;
	int msg_size ;

	struct sockaddr_in server;
	int c_sock;

	c_sock = socket(AF_INET,SOCK_DGRAM,0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(serverPort);
	len = sizeof(server);
	msg.msg_type = 1;
	memcpy(msg.msglength,id,sizeof(id));

	sendto(c_sock,&msg,sizeof(struct message),MSG_CONFIRM,(struct sockaddr *)&server,len);

	bzero(buff,BUF_SIZE);
	msg = {};
	msg_size = recvfrom(c_sock,&msg,sizeof(struct message),MSG_WAITALL,(struct sockaddr *)&server,&len);
	if(msg.msg_type == 0)
	{
		cout << "updated the registration" << endl;
		memcpy(buff,msg.msglength,sizeof(msg.msglength));
		cout << buff;
	}
	else{
		cout << "new registration" << endl;
	}
	

	return c_sock;

}

//to retrieve the id and port number of the person with whom you are chatting 
struct entry retrieveID(const char* id)
{
	char buff[BUF_SIZE];
	socklen_t len;
	int msg_size ;
	const char *IP = serverIP;
	struct sockaddr_in server;
	int c_sock;
	struct message msg;
	struct entry e;

	c_sock = socket(AF_INET,SOCK_DGRAM,0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(serverPort);
	len = sizeof(server);
	msg.msg_type = 2;
	memcpy(msg.msglength,id,sizeof(id));

	sendto(c_sock,&msg,sizeof(struct message),MSG_CONFIRM,(struct sockaddr *)&server,len);
	msg = {};
	msg_size = recvfrom(c_sock,&msg,sizeof(struct message),MSG_WAITALL,(struct sockaddr *)&server,&len);
	if(msg.msg_type == 3)
	{
		cout << "ID not present, please give correct ID!!"  << endl;
	}
	else
		{
			// cout << "ID present " << endl ;
			memcpy(&e,&msg.msglength[0],sizeof(struct entry));
			
			// cout << e.ID << " "<< e.IP << " "<< e.port << endl;
		 }
	
	close(c_sock);
	
	return e;
		
}

//client to client (other than DNS) 
//send message to other client/user
void send_text(int sock_fd,const char *id)
{
	while(1)
	{
		cout << "Give id message,for eg., alice hiii "<<endl;
		string ID,textt;
		cin >> ID >> textt;
		struct entry e;
		struct display_msg m;

		e = retrieveID(ID.c_str());
		memcpy(&m.ID,id,sizeof(id));
		memcpy(&m.text,textt.c_str(),sizeof(textt));
		sendmessage(sock_fd,e,m);

	}
}

void sendmessage(int sock_fd,struct entry e,struct display_msg m)
{
	struct sockaddr_in peer;
	// struct message msg;
	int sendsize;
	
	peer.sin_family = AF_INET;	
	peer.sin_addr.s_addr = inet_addr(e.IP);
	peer.sin_port = htons(e.port);

	sendsize = sendto(sock_fd, &m, sizeof(struct display_msg),MSG_CONFIRM,(const struct sockaddr *)&peer,sizeof(peer));
	if(sendsize > 0)
		cout << "message sent ...\n";
}


//receive text from other client/users.
void recv_text(int sock_fd)
{
	while(1)
	{
		struct sockaddr_in peer;
		struct display_msg msg;
		socklen_t t;
		t = sizeof(peer);
		recvfrom(sock_fd,&msg,sizeof(struct display_msg),MSG_WAITALL,(struct sockaddr*)&peer,&t);
	
		cout << "message received from "<< msg.ID<< " : " << msg.text<< endl;
	}
}
