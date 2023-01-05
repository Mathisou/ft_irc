#include "Client.hpp"
#include <errno.h>
#include <stdio.h>
#include <string.h>


client::client(const std::string &port, const std::string &password) : _port(port), _password(password){
	this->_sockclient = newSocket();
}

client::~client(){close(this->_sockclient);}

int client::newSocket()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		throw std::runtime_error("Error creating socket.\n");
	int tmp = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)))
		throw std::runtime_error("Error while setting up socket.\n");
	struct sockaddr_in client;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(std::stoi(_port));
	client.sin_family = AF_INET;
	// if (bind(sock, (const struct sockaddr*)&client, sizeof(client)) < 0)
	// 	throw std::runtime_error("Error binding socket.\n");
	if (connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0)
		throw std::runtime_error("Socket cannot connect.");
	return sock;
}

void client::sendMessage(std::string message) const
{
	message += "\r\n\0";
	if (send(this->_sockclient, message.c_str(), message.length(), 0) < 0)
		throw std::runtime_error("Error sending message.");
}

int client::verifpswd(std::string pswd)
{
	this->sendMessage(pswd);
	return (0);
}

std::string client::receiveMessage() const
{
	char buffer[1024];
	std::string message;

	memset(buffer, 0, 1024);

	if (recv(this->_sockclient, buffer, 1024, 0) < 0)
		throw std::runtime_error("Error receiving message");
	message = buffer;
	return message;
}