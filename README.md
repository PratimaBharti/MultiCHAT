
# multiCHAT

multiCHAT is an ID based chat application build using socket programming,multithreading concept in c++.You can chat with your friends using their name as ID. :)

## What you need

1. This chat application works in between two or more than two users and one server present. So, you need atleast three systems.
2. Change the server IP address in client/myheader.h to the IP address of the system which you are running as a DNS Server. If testing locally you need to change it to local IP 127.0.0.1

## Features and functionalities

1. The user(client) can start the chat with any other user(client).

2. The DNS_server keeps a record of all the users that are active and their IP address and port number.

3. The user is automatically registered(IP address and port number) to the DNS when it starts the client program. If the IP and port number of user system is already present with other's name(ID) in the DNS, it gets updated with the current user ID.

4. The DNS server is used to retrieve the IP address and port number of an ID the user wants to chat.



## How to run ?

If you are running locally, use makefile
Run "make all"
   1. Firstly,at DNS server side,compile and run the server file.

    g++ DNS_server.cpp -o server
    ./server

   2. Next,at client side,compile client file.

    g++ -o client client.cpp clientFunc.cpp

    to run it :
    ./client {Your ID}
    eg.  ./client Pratima
    


    
## Demo

Insert gif or link to demo

https://drive.google.com/file/d/1pxuV9d2zJeQCVoSY-JR9kOQCYDB-5k3W/view?usp=sharing
