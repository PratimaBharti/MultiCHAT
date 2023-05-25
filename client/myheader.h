#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <errno.h> 
#include<thread>



#define serverPort 8001

// change the server ip address to the ip address of system where DNS_server is running
// #define serverIP "127.0.0.1"
#define serverIP "172.16.15.6"

#define BUF_SIZE 1024
#define payload 1024


using namespace std;

struct message
{
	int msg_type;
    char msglength[payload];
};


struct entry
{
   char ID[20];
	 char IP[20];
	int port;
};

struct display_msg
{
	char ID[20];
	char text[30];
};


int registerID(const char*);
struct entry retrieveID(const char*);
void send_text(int,const char *);
void sendmessage(int,struct entry ,struct display_msg);
void recv_text(int);

