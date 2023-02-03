#ifndef MAIN_HPP
# define MAIN_HPP

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "User.hpp"
#include "Command.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "RPL_ERR.hpp"

# define SERVER_NAME "localhost"
# define ver "1.0"
# define USER_MODE "ior"
# define CHANNEL_MODE "ovamntlkb"
# define OPER_PW "5498"

# define FIND_USER(sd) \
    serv->getUsers().find(sd)->second

# define FIND_CHANNEL(channel_name) \
    serv->getChannels().find(channel_name)->second

#define max_clients 10

#define endBuf std::string("\r\n")
#define sep std::string(" \r\n")

class Server;
class User;
class Channel;

std::string user_output(User *user);
std::string anonymous_output();
void disconnectUser(Server *serv, int sd);
void sendMessage(std::string message, int sd);
void sendEveryoneInChan(std::string message, Channel *chan);
void sendEveryoneInChanExceptUser(std::string message, Channel *chan, int sd);
void sendEveryone(std::string message, std::map<int, User *> users);
bool nickname_is_in_use(Server *serv, std::string nick);

#endif