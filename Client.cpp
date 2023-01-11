#include "Client.hpp"
#include <errno.h>
#include <stdio.h>
#include <string.h>


Client::Client(std::string nick, std::string user, std::string hostname, std::string real_name) : _nick(nick), _user(user), _hostname(hostname), _real_name(real_name), _is_connect(false), _is_oper(false){
}

Client::~Client(){}

std::string Client::getNick()
{
    return this->_nick;
}

std::string Client::getUser()
{
    return this->_user;
}

std::string Client::getHostname()
{
    return this->_hostname;
}

std::string Client::getReal_name()
{
    return this->_real_name;
}