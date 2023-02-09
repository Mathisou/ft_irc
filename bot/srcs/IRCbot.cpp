#include "../../includes/main.hpp"

IRCbot::IRCbot() : _name("Armendes the BOT")
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
        std::cout << "test" << std::endl;
        // std::string botAnswer = botOutput(serv->getBot().getName());
        // botAnswer = serv->getBot().getName() + " JOIN " + chan->getChannelName();
        sendEveryoneInChan(serv->getBot().getName() + "!bot@bot JOIN " + chan->getChannelName(), chan);
    }
}

void quit(Server *serv, Channel *chan, int sd)
{
    (void)sd;
    if (chan && chan->getBot() == true)
    {
        chan->setBot();
        // std::string botAnswer = botOutput(serv->getBot().getName());
        // botAnswer += "PART " + chan->getChannelName();
        sendEveryoneInChan(serv->getBot().getName() + "!bot@bot PART " + chan->getChannelName(), chan);
    }
}

void makeJoke(Server *serv, Channel *chan, int sd)
{
    (void)serv;
    (void)chan;
    (void)sd;
    int jokesCount = 0;
    std::string infile("blagues.txt");
    std::ifstream in(infile.c_str());
    if (!in.is_open())
        return ;
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
    // return line;
}