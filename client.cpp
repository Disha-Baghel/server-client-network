#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <thread>

void sendMessage (int clientSocket) {
	while(true) {
	char* message = new char[1000];
	std::cout<<"Client: ";
	std::cin.getline(message, 1000);
	send(clientSocket, message, strlen(message), 0); 
	}

}

void receiveMessage (int clientSocket) {
	while(true) {
		char buffer[1024] = {0};
		recv(clientSocket, buffer, sizeof(buffer), 0);
		std::cout<< "Server: "<< buffer <<std::endl;
	}

}

int main() { 
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 

	sockaddr_in serverAddress; 
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_port = htons(8080); 
	serverAddress.sin_addr.s_addr = INADDR_ANY; 

	connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); 
	
	std::thread send (sendMessage, clientSocket);
	std::thread receive (receiveMessage, clientSocket);

		
	send.join();
	receive.join();


	close(clientSocket);

	return 0;
}