# Run the 'make' command from your terminal only if you are running both the server and the client on the same computer.
# Run 'make client' if you want to compile the client only. Similarly, 'make server' if you ....
#Run 'make clean all' to delete all the object files
# If client and server are running in different computers then copy the following commands and run in the terminals of the appropriate computers.

all: client server

client:
	@echo "Compiling the Client..."
	g++ -o client client.cpp clientFunc.cpp

server:
	@echo "Compiling the Server..."
	g++ DNS_server.cpp -o server

clean:
	@echo "Removing all object files..."
	rm client server
