#include "Server.hpp"
			         #include <string.h>

Server::Server(const std::string &port, const std::string &password) : _port(port), _password(password){
	this->_sockserver = newSocket();
}

Server::~Server(){close(this->_sockserver);}

int Server::newSocket()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		throw std::runtime_error("Error creating socket.\n");
	int tmp = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)))
		throw std::runtime_error("Error while setting up socket.\n");
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error while setting socket NON-BLOCKING mode.\n");
	struct sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(std::stoi(_port));
	server.sin_family = AF_INET;
	if (bind(sock, (const struct sockaddr*)&server, sizeof(server)) < 0)
		throw std::runtime_error("Error binding socket.\n");
	if (listen(sock, 1000) < 0)
		throw std::runtime_error("Error listening on socket.\n");
	struct sockaddr_in client;
	socklen_t csize = sizeof(client);
	if (accept(sock, (struct sockaddr*)&client, &csize) < 0)
	{
		std::cout << strerror(errno) << std::endl;
		throw std::runtime_error("Error accepting new socket.\n");
	}
	std::cout << "accept" << std::endl;
	return sock;
}

void Server::connectToServer()
{
	pollfd server_fd = {_sockserver, POLLIN, 0};
	std::cout << "listening..." << std::endl;
	while (1)
	{
		if (poll(&server_fd, 1, -1) < 0)
			throw std::runtime_error("Error while polling from fd.");
		// this->sendMessage("JOIN #mychannel\r\n");
		std::cout << "poll" << std::endl;
		// std::cout << this->receiveMessage() << std::endl;
	}
}

// void Server::sendMessage(std::string message) const
// {
// 	if (send(this->_sockserver, message.c_str(), message.size(), 0) < 0)
// 		std::cerr << "Error sending message." << std::endl;
// }

std::string Server::receiveMessage() const
{
	char buffer[1024];
	std::string message;

	if (recv(this->_sockserver, buffer, 1024, 0) < 0)
		throw std::runtime_error("Error receiving message");

	message = buffer;
	return message;
}
