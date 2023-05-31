// #include "myheader.h"
#include "dns_header.h"

// id ip port
unordered_map<string,pair<string,int>> DNS_Server;  

class DNS
{
	public:

	// to register the new user or update the current 
	int update_entry(string id,string ip,int port)
	{
		int flag = 0;
		if(DNS_Server.find(id) != DNS_Server.end())
		{
			cout <<"ID is present  "<< id <<" " <<DNS_Server[id].first << "  "<< DNS_Server[id].second << endl;
			DNS_Server[id] ={ip,port};
			sleep(1);
			cout << "Updated\n";		
		}
		else
		{
			cout << "ID not present" << endl;
			DNS_Server[id] = {ip,port};
			sleep(1);
			cout <<"Registered "<<id <<" "<< DNS_Server[id].first << "  "<< DNS_Server[id].second <<endl;
			flag = 1;
		}
		return flag;
	} 

	int retrieve_entry(string id,struct message &msg)
	{
		int flag = 0;
		struct entry e;
		if(DNS_Server.find(id) != DNS_Server.end())
		{	
			memcpy(&e.ID,id.c_str(),sizeof(id));
			string ip = DNS_Server[id].first;
			memcpy(&e.IP,ip.c_str(),sizeof(ip));
			e.port = DNS_Server[id].second;
			flag = 1;
			// cout << e.ID << " " << e.IP << " "<<e.port << endl;
			memcpy(&msg.msglength[0],&e,sizeof(struct entry));
		}

		return flag;
	}
	
	
};

class start
{
public:
	entry e;
	void server_start()
	{
		struct sockaddr_in server,client;
		int sock_fd;
		socklen_t client_addr_len;
		int client_port;
		char *client_IP;
		struct message msg;
		struct entry e;


		sock_fd = socket(AF_INET,SOCK_DGRAM, 0);

		if(sock_fd < 0)
		{
			cout << "socket creation failed\n";
			exit(1);
		}

		bzero(&server,sizeof(server));

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(serverPort);


		if( bind(sock_fd,(struct sockaddr *)&server, sizeof(server)) <0){
			perror("bind failed");
        	exit(EXIT_FAILURE);
		}	

		listen(sock_fd,10);

		cout << "DNS server started...\n";

		char buff[BUF_SIZE];
		// DNS table;
		DNS dns;

		while(1)
		{
			bzero(&client,sizeof(client));
			bzero(&buff,sizeof(buff));
			client_addr_len = sizeof(client);
			recvfrom(sock_fd,&msg,sizeof(struct message),MSG_WAITALL,(struct sockaddr*)&client,&client_addr_len);
			client_IP = inet_ntoa(client.sin_addr);
			client_port = htons(client.sin_port);

			//1 -- register 2 -- retrieve
			int flag ;
			if(msg.msg_type == 1)
			{
				bzero(&buff,BUF_SIZE);
				memcpy(&buff,&msg.msglength[0],sizeof(msg.msglength));
				cout << buff << endl;
				flag = dns.update_entry(string(buff),string(client_IP),client_port);
				sleep(1);
				msg.msg_type = 1;
				string m = "updated";
				memcpy(msg.msglength,&m,sizeof(m));
			}
			else if(msg.msg_type == 2)
			{
				bzero(&buff,BUF_SIZE);
				memcpy(&buff,&msg.msglength[0],sizeof(msg.msglength));
				cout <<"requested ID "<< buff << endl;
				sleep(1);
				bzero(&msg,sizeof(struct message));
				e = {};
				flag = dns.retrieve_entry(string(buff),msg);
				if(flag) 
				{
					msg.msg_type = 2;  //present
					cout << "present" << endl;
					// cout << e.ID << endl;
				}
				
				else
				{
					msg.msg_type = 3 ; //not present
					cout << "not present" << endl;
				}

			}
			
				sendto(sock_fd,&msg,sizeof(struct message),MSG_CONFIRM,(struct sockaddr *)&client,client_addr_len);
				sleep(1);
			
		}

		close(sock_fd);
	}
};

int main(int argc,char *argv[])
{
	start s;
	s.server_start();

	return 0;
}

