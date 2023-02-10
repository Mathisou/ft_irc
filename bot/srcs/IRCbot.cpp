#include "../../includes/main.hpp"

IRCbot::IRCbot() : _name("ArmendestheBOT")
{
	this->_commandhandler.insert(std::pair<std::string, command>("wakeup", &connect));
    this->_commandhandler.insert(std::pair<std::string, command>("help", &help));
    this->_commandhandler.insert(std::pair<std::string, command>("joke", &makeJoke));
    this->_commandhandler.insert(std::pair<std::string, command>("date", &giveDate));
    this->_commandhandler.insert(std::pair<std::string, command>("time", &giveTime));
    this->_commandhandler.insert(std::pair<std::string, command>("hangman", &hangmanGame));
    this->_commandhandler.insert(std::pair<std::string, command>("sleep", &quit));
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
    if (chan->isChanop(sd))
    {
        if (chan && chan->getBot() == false)
        {
            chan->setBot();
            sendEveryoneInChan(":" + serv->getBot().getName() + " JOIN " + chan->getChannelName(), chan);
        }
        else
            sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :I am already awake.", sd);
    }
    else
        sendMessage(sendRplErr(482, serv, FIND_USER(sd), chan->getChannelName(), ""), sd);
}

void quit(Server *serv, Channel *chan, int sd)
{
    if (chan->isChanop(sd))
    {
        if (chan && chan->getBot() == true)
        {
            chan->setBot();
            sendEveryoneInChan(":" + serv->getBot().getName() + " PART " + chan->getChannelName(), chan);
        }
        else
            sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :I am sleeping right now, wake me up to play with me.", sd);
    }
    else
        sendMessage(sendRplErr(482, serv, FIND_USER(sd), chan->getChannelName(), ""), sd);
}

void makeJoke(Server *serv, Channel *chan, int sd)
{
    int lines = 0;
    if (chan && chan->getBot() == true)
    {
        srand(time(NULL));
        time_t delay = getTime() - chan->getLastJoke();
        if (delay >= 15)
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
            chan->setLastJoke();
        }
        else
        {
            long a = 15 - delay;
            std::stringstream ss;
            ss << a;
            sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :You have to wait " + ss.str() + " seconds before sending another joke!", sd);
        }
    }
    else
        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :I am sleeping right now, wake me up to play with me.", sd);
}

void giveTime(Server *serv, Channel *chan, int sd)
{
    if (chan && chan->getBot() == true)
    {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::stringstream sshour;
        sshour << now->tm_hour;
        std::stringstream ssmin;
        ssmin << now->tm_min;
        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :It is " + sshour.str() + ":" + ssmin.str() + ".", sd);
    }
    else
        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :I am sleeping right now, wake me up to play with me.", sd);

}

void giveDate(Server *serv, Channel *chan, int sd)
{
    if (chan && chan->getBot() == true)
    {
        std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::stringstream ssyear;
        ssyear << now->tm_year + 1900;
        std::stringstream ssmday;
        if (now->tm_mday == 1)
            ssmday << now->tm_mday << "st";
        else if (now->tm_mday == 2)
            ssmday << now->tm_mday << "nd";
        else if (now->tm_mday == 3)
            ssmday << now->tm_mday << "rd";
        else
            ssmday << now->tm_mday << "th";

        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :Today we are on " + months[now->tm_mon] + " " + ssmday.str() + " of " + ssyear.str() + ".", sd);
    }
    else
        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :I am sleeping right now, wake me up to play with me.", sd);
}

void help(Server *serv, Channel *chan, int sd)
{
    std::string line = "!wakeup  - Connect the bot to the channel.";
    sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, sd);
    line = "!joke    - Let the bot make a joke.";
    sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, sd);
    line = "!date    - Give today's date.";
    sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, sd);
    line = "!time    - Give the current time. (UTC+1)";
    sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, sd);
    line = "!hangman - Play the hangman game.";
    sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, sd);
    line = "!sleep   - Disconnect the bot.";
    sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :" + line, sd);
}

void hangmanGame(Server *serv, Channel *chan, int sd)
{
    int lines = 0;
    if (chan && chan->getBot() == true)
    {
        srand(time(NULL));
        std::string word;
        std::ifstream file("bot/srcs/mots.txt");
        if (file.is_open())
        {
            while (std::getline(file, word))
                lines++;
            file.close();
            int random = rand() % lines;
            std::ifstream file("bot/srcs/mots.txt");
            if (file.is_open())
            {
                for (int i = 0; i < lines; i++)
                {
                    std::getline(file, word);
                    if (i == random)
                        break;
                }
                file.close();
            }
        }
        std::cout << "bonjour" << std::endl;
        std::string result;
        result.insert(0, word.size(), '_');
        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + FIND_USER(sd)->getNickname() + " :You are playing Hangman Game, enter a letter to start the game.", sd);
    }
    else
        sendMessage(":" + serv->getBot().getName() + " PRIVMSG " + chan->getChannelName() + " :I am sleeping right now, wake me up to play with me.", sd);
}
