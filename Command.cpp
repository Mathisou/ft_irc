#include "Command.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "RPL_ERR.hpp"

std::string user_output(User *user);

void nick(Server *serv, char *buffer, int sd)
{
    int i = 0;
    std::string buf(buffer);
    for (; buf[5 + i] && buf[5 + i] != ' ' && buf[5 + i] != '\r' && buf[5 + i] != '\n';i++);
    std::string new_nickname(buf.substr(5, i));
    std::string user_answer = user_output(serv->getUsers().find(sd)->second);
    user_answer += buffer;
    std::cout << user_answer << std::endl;
    serv->sendMessage(user_answer, sd);
    serv->getUsers().find(sd)->second->setNick(new_nickname);
}

void join(Server *serv, char *buffer, int sd)
{
    int i = 0;
    std::string buf(buffer);
    for (; buf[5 + i] && buf[5 + i] != ' ' && buf[5 + i] != '\r' && buf[5 + i] != '\n';i++);
    std::string channel_name(buf.substr(5, i));
    if (serv->getChannels().find(channel_name) == serv->getChannels().end()) // si le channel n'existe pas on le cree et on l'ajoute a notre map de channel
	{
		Channel *chan = new Channel(channel_name);
    	serv->setChannels(channel_name, chan);
	}
	//On ajoute le client a notre serveur
    // std::cout << serv->getChannels() << std::endl;
    if (serv->getChannels().find(channel_name)->second->getUsersnumber() == 0)
        serv->getChannels().find(channel_name)->second->addOper(sd, serv->getUsers().find(sd)->second);
    else
	    serv->getChannels().find(channel_name)->second->addUser(sd, serv->getUsers().find(sd)->second);
    serv->getUsers().find(sd)->second->add_channel(channel_name);
    std::string user_answer = user_output(serv->getUsers().find(sd)->second);
    user_answer += buffer;
    serv->sendMessage(user_answer, sd);
    serv->sendMessage(send_rpl_err(332, serv, serv->getUsers().find(sd)->second, channel_name, ""), sd);
    std::string list_of_user = serv->getChannels().find(channel_name)->second->get_list_of_user_in_chan();
    std::cout << list_of_user << std::endl;
    serv->sendMessage(send_rpl_err(353, serv, serv->getUsers().find(sd)->second, channel_name, list_of_user), sd);
    serv->sendMessage(send_rpl_err(366, serv, serv->getUsers().find(sd)->second, channel_name, ""), sd);
    // serv->sendMessage(send_rpl_err(serv, serv->getUsers().find(sd)->second, ))
    // std::cout << serv->getUsers() << std::endl;
    // std::cout << serv->getChannels().find(channel_name)->second->getUsers() << std::endl;
}

void privmsg(Server *serv, char *buffer, int sd)
{
    std::cout << buffer << std::endl;
    int i = 0;
    std::string buf(buffer);
    for (; buf[8 + i] && buf[8 + i] != ' ' && buf[8 + i] != '\r' && buf[8 + i] != '\n';i++);
    std::string channel_name(buf.substr(8, i));
    std::cout << "channel_name : " << channel_name << "lol" << std::endl;
    std::map<std::string, Channel*> channels = serv->getChannels();
	std::map<std::string, Channel*>::iterator test =  channels.find(channel_name);
	std::cout << "hihihihi : " << test->first << std::endl; //si on retire ce print ca segfault (sur mac en tout cas)
	Channel *channel = test->second;
    std::map<int, User*> users = channel->getUsers();
	std::cout << channel->getUsersnumber() << std::endl;
    std::map<int, User*>::iterator end = users.end();
	for (std::map<int, User*>::iterator it = users.begin(); it != end; it++)
    {
		//std::cout << "yo" << std::endl;
        if (sd != it->first)
            serv->sendMessage(buffer, it->first);
    }
}

// void ping(Server *serv, char *buffer, int sd)
// {
//     buffer[1] = 'O';
//     serv->sendMessage(buffer);
//     std::cout << "test2 " << buffer << std::endl;
// }

// void pong(Server *serv, char *buffer, int sd)
// {
//     buffer[1] = 'I';
//     serv->sendMessage(buffer);
//     std::cout << "test3" << std::endl;
// }

// void user()
// {
//     std::cout << "test2" << std::endl;
// }
