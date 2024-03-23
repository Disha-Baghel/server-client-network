#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

using namespace std;

void sendMessage (int clientSocket) {

	while(true) {
		char *message = new char[1000];
		cout << "Server: ";
		cin.getline(message, 1000);

		send(clientSocket, message, strlen(message), 0);
	}

}

void receiveMessage (int clientSocket) {
	while (true) {
		char buffer[1024] = {0};
		recv(clientSocket, buffer, sizeof(buffer), 0);
		cout << "Message from client: " << buffer << endl;
	}
} 

int main() {
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

	listen(serverSocket, 5);

	int clientSocket = accept(serverSocket, nullptr, nullptr);

	std::thread send(sendMessage, clientSocket);
	std::thread receive(receiveMessage, clientSocket);

	send.join();
	receive.join();

	close(serverSocket);

	return 0;
}