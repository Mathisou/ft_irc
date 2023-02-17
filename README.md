Usage :

`brew install irssi`
    
`make`
    
`./server <port> <password>`

NOTE :
  - Only irc port are allowed. (6660->6669, 6679 and 6697).
  - The password have to contains only 4 digits and nothing else.

This project was carried out in teams of 2.

We created an IRC server based on RFC 2812.

You should be able to use the client of your choice, but keep in mind that we did it with IRSSI and didnt test it out with other clients.
It is working with netcat too.

Commands handled:
- `JOIN <channel>`
- `NICK <new_nickname>`
- `PRIVMSG <nickname> <message>`
- `NOTICE <nickname> <message>`
- `MODE <channel> <ovamntlkb>`
- `MODE <nickname> <ior>`
- `PART <channel> <message>`
- `TOPIC <channel> <message>`
- `KICK <channel> <nickname>`
- `OPER <nickname> <oper password>`
- `KILL <nickname>`
- `QUIT <message>`
- `RESTART`
    
How to use:

IRSSI:
        
- First open IRSSI typing `irssi` on the bash
- Connect with `/connect <ip> <port> <password>`
- Then you should start all commands with a `/` followed by one of the command above.
- You can type `/help` to see all irssi commands (even those we dont handle) because some commands have a different syntax. (Example: PRIVMSG -> /msg)
          
netcat:
      
- Type `nc <ip> <port>` on the bash
- First you have to enter the server password `PASS <password>`
- Then your nickname `NICK <nickname>`
- Finally your username, hostname, server name and real name `USER <username> <hostname> <server name> <real name>`
- If one of those steps went wrong, you have to do restart the connexion process.
- Otherwise well played you are connected on the server!
- To use commands now, you have to follow the syntax above.


Enjoy your chat with your friends !
