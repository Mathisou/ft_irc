#include "main.hpp"

bool isBotCmd(std::string buffer)
{
    int i = 0;
    int j;
    for (j = 0;buffer[j] && i < 2;j++)
        if (buffer[j] == ' ')
            i++;
    std::cout << buffer[j] << std::endl;
    if (buffer[j] == '!' || (buffer[j] == ':' && buffer[j + 1] == '!'))
        return true;
    return false;
}

void privmsg(Server *serv, std::string buffer, int sd)
{
    int i = 0;
    int occAfterCmd;
    std::string buf(buffer);
    if (buf.compare(0, 6, "NOTICE") == 0)
        occAfterCmd = 7;
    else
        occAfterCmd = 8;
    for (; buf[occAfterCmd + i] && sep.find(buf[occAfterCmd + i]) == std::string::npos;i++);
    std::string msgtarget(buf.substr(occAfterCmd, i));
    std::string idOfChannel = "#&+";

    int userToSendSd;
    std::string user_answer;
    user_answer = userOutput(FIND_USER(sd));
    user_answer += buffer;
    if (!msgtarget.empty() && idOfChannel.find(msgtarget[0]) != std::string::npos)
    {
        if (serv->getChannels().find(msgtarget) == serv->getChannels().end())
            sendMessage(send_rpl_err(401, serv, FIND_USER(sd), msgtarget, ""), sd);
        else if ((FIND_CHANNEL(msgtarget)->getMode().find("n") != std::string::npos) && (FIND_CHANNEL(msgtarget)->searchUserByNickname(FIND_USER(sd)->getNickname()) == -1))
            sendMessage(send_rpl_err(404, serv, FIND_USER(sd), msgtarget, ""), sd);
        else if ((FIND_CHANNEL(msgtarget)->getMode().find("m") != std::string::npos) && (!FIND_CHANNEL(msgtarget)->isChanop(sd)) && (!FIND_CHANNEL(msgtarget)->isVoices(sd)))
            sendMessage(send_rpl_err(404, serv, FIND_USER(sd), msgtarget, ""), sd);
		else if (FIND_CHANNEL(msgtarget)->isBan(FIND_USER(sd)->getNickname()) == true || FIND_CHANNEL(msgtarget)->isBan(FIND_USER(sd)->getUsername()) == true || FIND_CHANNEL(msgtarget)->isBan(FIND_USER(sd)->getHostname()) == true)
            sendMessage(send_rpl_err(404, serv, FIND_USER(sd), msgtarget, ""), sd);
        else if (FIND_USER(sd)->getMode().find('o') != std::string::npos && isBotCmd(buffer) == true)
        {
            std::string command = buffer.substr(buffer.find('!') + 1, buffer.find('\r') != std::string::npos ? buffer.length() - 2 - (buffer.find('!') + 1): buffer.length() - 1 - (buffer.find('!') + 1));
            std::cout << "[" << command << "]" << std::endl;
            serv->getBot().findCmd(serv, FIND_CHANNEL(msgtarget), sd, command);
        }
        else if ((FIND_CHANNEL(msgtarget)->getMode().find("a") != std::string::npos))
        {
            user_answer = anonymousOutput() + buffer;
            sendEveryoneInChanExceptUser(user_answer, FIND_CHANNEL(msgtarget), sd);
        }
        else
            sendEveryoneInChanExceptUser(user_answer, FIND_CHANNEL(msgtarget), sd);
    }
    else
    {
        if ((userToSendSd = serv->searchUserByNickname(msgtarget)) == -1)
            sendMessage(send_rpl_err(401, serv, FIND_USER(sd), msgtarget, ""), sd);
        else
            sendMessage(user_answer, userToSendSd);
    }
    
}
