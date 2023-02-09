#pragma once

#include "../../includes/main.hpp"

class Server;
class Channel;

class IRCbot
{
	typedef void (*command)(Server *, Channel *, int);

	private:
		std::map<std::string, command> _commandhandler;
		std::string _name;
		std::set<std::string> _channels;

	public:

		IRCbot();
		virtual ~IRCbot();
		std::string getName() const;
		void addChannel(std::string channelName);
		void findCmd(Server * serv, Channel *chan, int sd, std::string cmd);
};

void connect(Server *serv, Channel *chan, int sd);
void quit(Server *serv, Channel *chan, int sd);
void makeJoke(Server *serv, Channel *chan, int sd);