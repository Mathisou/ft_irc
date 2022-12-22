#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server{

	private:

	int _sockserver;
	//int _sockclient;
	const std::string _port;
	const std::string _password;

	public:

	Server(const std::string &port, const std::string &password);
	~Server();
	void connectToServer();
	int newSocket();
	void sendMessage(std::string message) const;
	std::string receiveMessage() const;

};

#endif