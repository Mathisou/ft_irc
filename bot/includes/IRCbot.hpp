#pragma once

#include "../../includes/main.hpp"

class Server;
class Channel;

class IRCbot
{
	typedef void (*command)(Server *, Channel *, int);

	private:
		std::map<std::string, command> _commandhandler;
		std::map<int, std::pair<std::string, std::string> > _hangmanWords;
		std::string _name;
		std::set<std::string> _channels;

	public:
		IRCbot();
		virtual ~IRCbot();
		std::string getName() const;
		std::map<int, std::pair<std::string, std::string> > & getHangmanWords();
		void addChannel(std::string channelName);
		void findCmd(Server * serv, Channel *chan, int sd, std::string cmd);
		void hangmanGame(Server *serv, char c, int sd);
		void insertWord(std::string message, std::string messageGuess, int sd);
};

void connect(Server *serv, Channel *chan, int sd);
void quit(Server *serv, Channel *chan, int sd);
void makeJoke(Server *serv, Channel *chan, int sd);
void giveTime(Server *serv, Channel *chan, int sd);
void help(Server *serv, Channel *chan, int sd);
void giveDate(Server *serv, Channel *chan, int sd);
void startHangmanGame(Server *serv, Channel *chan, int sd);
