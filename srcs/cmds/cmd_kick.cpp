#include "main.hpp"

void kick(Server *serv, char *buffer, int sd)
{
    std::string buf(buffer);
    int kickCount = std::count(buf.begin(), buf.end(), '\n');
    int i = 0;
    for (; buf[5 + i] && sep.find(buf[i]) == std::string::npos; i++);
    std::string channels_name(buf.substr(5, i));
    if (channels_name.empty())
    {
        sendMessage(send_rpl_err(461, serv, FIND_USER(sd), "KICK", ""), sd);
        return;
    }
    int nb_of_channels = 1 + std::count(channels_name.begin(), channels_name.end(), ',');
    int j = 0;
    for (; buf[i] && buf[i] != ':' && endBuf.find(buf[i]) == std::string::npos; i++);
    for (; buf[i + j] && endBuf.find(buf[i + j]) == std::string::npos; j++);
    std::string message = buf.substr(i + 1, j - 1);
    for (int k = 0; k < kickCount; k++)
    {
        j = i - 2;
        for (; (j >= 0) && buf[j] != ' '; j--);
        std::string user_nick = buf.substr((j + 1), (i - 2 - j));
        if (user_nick.empty())
        {
            sendMessage(send_rpl_err(461, serv, FIND_USER(sd), "KICK", ""), sd);
            return;
        }
        for (int i = 0; i < nb_of_channels; i++)
        {
            std::string channel_name = channels_name.substr(0, channels_name.find(","));
            channels_name.erase(0, channels_name.find(",") + 1);
            if (serv->getChannels().find(channel_name) == serv->getChannels().end())
            {
                sendMessage(send_rpl_err(403, serv, FIND_USER(sd), channel_name, ""), sd);
                continue;
            }
            if (FIND_CHANNEL(channel_name)->getMode().find("a") != std::string::npos)
                continue;
            if (FIND_CHANNEL(channel_name)->searchUserByNickname(FIND_USER(sd)->getNickname()) == -1)
            {
                sendMessage(send_rpl_err(442, serv, FIND_USER(sd), channel_name, ""), sd);
                continue;
            }
            if (FIND_USER(sd)->getMode().find('r') != std::string::npos)
            {
                sendMessage(send_rpl_err(484, serv, FIND_USER(sd), "", ""), sd);
                continue ;
            }
            if (!FIND_CHANNEL(channel_name)->isChanop(sd))
            {
                sendMessage(send_rpl_err(482, serv, FIND_USER(sd), channel_name, ""), sd);
                continue ;
            }
            int userToKickSd;
            if ((userToKickSd = FIND_CHANNEL(channel_name)->searchUserByNickname(user_nick)) == -1)
            {
                sendMessage(send_rpl_err(441, serv, FIND_USER(sd), user_nick, channel_name), sd);
                continue;
            }
            std::string user_answer = user_output(FIND_USER(sd));
            user_answer += buffer;
            sendEveryoneInChanExceptUser(user_answer, FIND_CHANNEL(channel_name), userToKickSd);
            FIND_CHANNEL(channel_name)->leftUser(userToKickSd);
            if (FIND_CHANNEL(channel_name)->getUsersnumber() == 0)
                serv->getChannels().erase(serv->getChannels().find(channel_name)->first);
            FIND_USER(userToKickSd)->getChannels().erase(channel_name);
            user_answer = user_output(FIND_USER(userToKickSd));
            user_answer += "PART " + channel_name;
            sendMessage(user_answer, userToKickSd);
        }
        if (buf.find('\r') != std::string::npos)
            buf.erase(0, buf.find("\r\n") + 2);
        else
            buf.erase(0, buf.find('\n') + 1); // a check
    }
}