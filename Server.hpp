#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.hpp"
#include <vector>
#include <map>

class Server{
	public:

		typedef void (*command)(void);

	private:

	int _sockserver;
	int _sockcom;
	const std::string _port;
	const std::string _password;
	std::map<std::string, Client*> _users;
	std::map<std::string, command> _commandhandler;
	struct sockaddr_in server;

	public:


	Server(const std::string &port, const std::string &password);
	~Server();
	void connectToServer();
	int newSocket();
	void sendMessage(std::string message) const;
	std::string receiveMessage() const;

};

#endif
