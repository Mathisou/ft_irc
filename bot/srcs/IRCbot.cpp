#include "../../includes/main.hpp"

IRCbot::IRCbot() : _name("ArmendestheBOT")
{
	this->_commandhandler.insert(std::pair<std::string, command>("connect", &connect));
    this->_commandhandler.insert(std::pair<std::string, command>("joke", &makeJoke));
    // this->_commandhandler.insert(std::pair<std::string, command>("time", &giveTime));
    // this->_commandhandler.insert(std::pair<std::string, command>("hangman", &hangmanGame));
    this->_commandhandler.insert(std::pair<std::string, command>("quit", &quit));
}

IRCbot::~IRCbot(){this->_channels.clear();}

void IRCbot::addChannel(std::string channelName)
{
    this->_channels.insert(channelName);
}

std::string IRCbot::getName() const
{
    return this->_name;
}

void IRCbot::findCmd(Server * serv, Channel *chan, int sd, std::string cmd)
{
    if (_commandhandler.find(cmd) != _commandhandler.end())
        this->_commandhandler[cmd](serv, chan, sd);
}

void connect(Server *serv, Channel *chan, int sd)
{
    (void)sd;
    if (chan && chan->getBot() == false)
    {
        chan->setBot();
        sendEveryoneInChan(":" + serv->getBot().getName() + " JOIN " + chan->getChannelName(), chan);
    }
}

void quit(Server *serv, Channel *chan, int sd)
{
    (void)sd;
    if (chan && chan->getBot() == true)
    {
        chan->setBot();
        sendEveryoneInChan(":" + serv->getBot().getName() + " PART " + chan->getChannelName(), chan);
    }
}

void makeJoke(Server *serv, Channel *chan, int sd)
{
    int lines = 0;
    if (chan && chan->getBot() == true)
    {
        std::string line;
        std::ifstream file("bot/srcs/blagues.txt");
        if (file.is_open())
        {
            while (std::getline(file, line))
                lines++;
            file.close();
            int random = rand() % lines;
            std::ifstream file("bot/srcs/blagues.txt");
            if (file.is_open())
            {
                for (int i = 0; i < lines; i++)
                {
                    std::getline(file, line);
                    if (i == random)
                        break;
                }
                file.close();
            }
        }
        sendEveryoneInChan(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, chan);
    }
    else
    {
        std::string userAnswer = userOutput(FIND_USER(sd));
        userAnswer += " PRIVMSG " + chan->getChannelName() + " :There is no bot in this channel.";
        sendEveryoneInChan(userAnswer, chan);
    }
}