#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

class client{
	private:
	int _sockclient;
	std::string _port;
	std::string _password;

	public:
	client(const std::string &port, const std::string &password);
	~client();
	void sendMessage(std::string message) const;
	std::string receiveMessage() const;
	int newSocket();
	int verifpswd(std::string pswd);
};

#endif