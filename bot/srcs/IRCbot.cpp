#include "IRCbot.hpp"

IRCbot::IRCbot() : _name("Armendes the BOT"){}

IRCbot::~IRCbot(){this->_channels.clear();}

std::string IRCbot::makeJoke()
{
    int jokesCount = 0;
    std::string infile("blagues.txt");
    std::ifstream in(infile.c_str());
    if (!in.is_open())
        return NULL;
    std::string line;
    for (;std::getline(in, line);jokesCount++)
        ;
    in.close();
    in.open("blagues.txt", std::ifstream::in);
    srand(time(NULL));
    int random = rand() % jokesCount;
    for (int j = 0;std::getline(in, line) && j < random; j++)
        ;
    in.close();
    return line;
}

void IRCbot::addChannel(std::string channelName)
{
    this->_channels.insert(channelName);
}