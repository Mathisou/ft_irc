#include "Server.hpp"

Server::Server(const std::string &port, const std::string &password) : _port(port), _password(password){}

Server::~Server(){}

void Server::connectToServer()
{
	this->_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sock < 0)
	{
		std::cerr << "Error creating socket." << std::endl;
		exit(1);
	}
	struct sockaddr_in server;
	// std::cout << server.sin_addr.s_addr << std::endl;
	server.sin_port = htons(static_cast<unsigned short>(std::strtoul(this->_port.c_str(), NULL, 0)));
	// server.sin_port = htons(atoi(this->_port.c_str()));
	server.sin_family = AF_INET;
	// inet_ntoa(server.sin_addr); // where to use inet_addr and inet_ntoa?
	if (connect(this->_sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		std::cerr << "Error connecting to server." << std::endl;
		exit(1);
	}
	std::cout << "Connection has been successfull." << std::endl;
}

void Server::sendMessage(std::string message) const
{
	if (send(this->_sock, message.c_str(), message.size(), 0) < 0)
	{
		std::cerr << "Error sending message." << std::endl;
		exit(1);
	}
}

std::string Server::receiveMessage() const
{
	char buffer[1024];
	std::string message;

	if (recv(this->_sock, buffer, 1024, 0) < 0)
	{
		std::cerr << "Error receiving message" << std::endl;
		exit(1);
	}

	message = buffer;
	return message;
}
