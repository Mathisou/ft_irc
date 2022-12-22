#include "Server.hpp"

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
	// std::cout << "bind" << std::endl;
	if (listen(sock, 1000) < 0)
		throw std::runtime_error("Error listening on socket.\n");
	// std::cout << "listen" << std::endl;
	return sock;
}

void Server::connectToServer()
{

}

// void Server::sendMessage(std::string message) const
// {
// 	if (send(this->_sock, sr(), message.size(), 0) < 0)
// 	{
// 		std::cerr << "Error sending message." << std::endl;
// 		exit(1);
// 	}
// }

// std::string Server::receiveMessage() const
// {
// 	char buffer[1024];
// 	std::string message;

// 	if (recv(this->_sock, buffer, 1024, 0) < 0)
// 	{
// 		std::cerr << "Error receiving message" << std::endl;
// 		exit(1);
// 	}

// 	message = buffer;
// 	return message;
// }
