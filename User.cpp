#include "User.hpp"
#include <errno.h>
#include <stdio.h>
#include <string.h>

int max_clients = 10;

User::User(std::string nick, std::string user, std::string hostname, std::string real_name) : _nick(nick), _user(user), _hostname(hostname), _real_name(real_name){
}

User &User::operator=(const User &T)
{
    if (this == &T)
        return (*this);
    this->_nick = T._nick;
    this->_user = T._user;
    this->_hostname = T._hostname;
    this->_real_name = T._real_name;
    return (*this);
}

User::User(const User &T)
{
	*this = T;
	return ;
}

User::~User(){}

std::string User::getNick() const
{
    return this->_nick;
}

std::string User::getUser() const
{ 
    return this->_user;
}

std::string User::getHostname() const
{
    return this->_hostname;
}

std::string User::getReal_name() const
{
    return this->_real_name;
}

std::vector<std::string> User::getChannels() const
{
    return this->_channels;
}

void User::add_channel(std::string channel_name)
{
    std::vector<std::string>::iterator it = find(this->_channels.begin(), this->_channels.end(), channel_name);
    if (it == this->_channels.end())
        this->_channels.push_back(channel_name);
}

void User::setNick(std::string new_nick)
{
    this->_nick = new_nick;
}

