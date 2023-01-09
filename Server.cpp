#include "Server.hpp"
#include <string.h>
#include "Command.cpp"

#define max_clients 10

Server::Server(const std::string &port, const std::string &password) : _port(port), _password(password){
	this->_sockserver = newSocket();
	this->_commandhandler.insert(std::make_pair("NICK", &nick));
	this->_commandhandler.insert(std::make_pair("userhost", &user));

	// _users = NULL;
}

Server::~Server(){close(this->_sockserver);}

int Server::newSocket()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		throw std::runtime_error("Error creating socket.\n");
	int tmp = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)))
		throw std::runtime_error("Error while setting up socket.\n");
	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error while setting socket NON-BLOCKING mode.\n");
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(std::stoi(_port));
	server.sin_family = AF_INET;
	if (bind(sock, (const struct sockaddr*)&server, sizeof(server)) < 0)
		throw std::runtime_error("Error binding socket.\n");
	if (listen(sock, 10) < 0)
		throw std::runtime_error("Error listening on socket.\n");
	// if (accept(sock, (struct sockaddr*)&client, &csize) < 0)
	// {
	// 	std::cout << strerror(errno) << std::endl;
	// 	throw std::runtime_error("Error accepting new socket.\n");
	// }
	std::cout << "accept" << std::endl;
	return sock;
}

void Server::connectToServer()
{
	// std::string buffer;
	char buffer[1025];
	// pollfd server_fd = {_sockserver, POLLIN, 0};
	fd_set readfds;
	int client_socket[max_clients], sd, activity, max_sd, valread;
	for (int i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
	// struct sockaddr_in client;
	socklen_t csize = sizeof(server);
	std::cout << "listening..." << std::endl;
	while (1)
	{
		// if (poll(&server_fd, 1, -1) < 0)
		// 	throw std::runtime_error("Error while polling from fd.");
		// std::cout << "poll" << std::endl;
		// this->_sockcom = accept(_sockserver, (struct sockaddr*)&client, &csize);
		// sendMessage("Enter the server password.");
	/*while (1)
		{
			std::string pswd;
			std::cin >> pswd;
			this->sendMessage(pswd);
			// std::cout << _sockcom << std::endl;
		}*/
		       //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(this->_sockserver, &readfds);  
        max_sd = this->_sockserver;  
             
        //add child sockets to set 
        for ( int i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }

		if (FD_ISSET(this->_sockserver, &readfds))  
        {  
            if ((this->_sockcom = accept(this->_sockserver, 
                    (struct sockaddr *)&server, &csize))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            // printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , this->_sockcom , inet_ntoa(address.sin_addr) , ntohs
            //       (address.sin_port));  
           
            //send new connection greeting message
			sendMessage("CAP * LS :multi-prefix sasl");
			std::cout << this->receiveMessage();
			sendMessage("CAP * ACK multi-prefix");
			std::cout << this->receiveMessage();
			sendMessage("001 maroly :Welcome to the Internet Relay Network maroly");
			std::cout << this->receiveMessage();
            // if( send(this->_sockcom, message, strlen(message), 0) != strlen(message) )  
            // {  
            //     perror("send");  
            // }  
                 
            // puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (int i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {
                    client_socket[i] = this->_sockcom;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }
            }
		}
		else
		{
			for (int i = 0; i < max_clients; i++)  
			{ 
				sd = client_socket[i];  
				if (FD_ISSET( sd , &readfds))  
				{
					//Check if it was for closing , and also read the 
					//incoming message
					// if ((valread = recv( sd , buffer, 1024, 0)) == 0)
					recv( sd , buffer, 1024, 0);
					if (strcmp(buffer, "QUIT :leaving"))  
					{  
						//Somebody disconnected , get his details and print 
						getpeername(sd , (struct sockaddr*)&server , &csize);  
						printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(server.sin_addr) , ntohs(server.sin_port));  
							
						//Close the socket and mark as 0 in list for reuse 
						close( sd );  
						client_socket[i] = 0;  
					}  
						
					//Echo back the message that came in 
					else 
					{  
						//set the string terminating NULL byte on the end 
						//of the data read
						std::cout << "valread is " << valread << std::endl;
						std::cout << strerror(errno) << std::endl;
						buffer[valread] = '\0'; 
						std::cout << buffer << std::endl;
						send(sd , buffer , strlen(buffer) , 0 );
						break;
					}  
				}  
			}
		}
	}

		// std::cout << this->receiveMessage();
		// // std::cout << "test" << std::endl;
		// sendMessage("CAP * LS :multi-prefix sasl");
		// std::cout << this->receiveMessage();
		// sendMessage("CAP * ACK multi-prefix");
		// std::cout << this->receiveMessage();
		// sendMessage("001 maroly :Welcome to the Internet Relay Network maroly");
		// std::cout << this->receiveMessage();
		// // while (1)
		// // {
		// 	buffer = this->receiveMessage();
		// 	if (buffer.find("PING") == 0)
		// 	{
		// 		std::cout << "DSAHDKJASHKJDHSKJHDASKJH " << buffer << std::endl;
		// 		buffer[1] = 'O';
		// 		sendMessage(buffer);
		// 	}
		// 	else{
		// 		std::string command = buffer.substr(0, buffer.find(' '));
		// 		std::cout << "MY NICK: " << command << std::endl;
		// 		if (_commandhandler.find(command) != _commandhandler.end())
		// 			(_commandhandler[command])();
		// 	}
		// }
	close(this->_sockcom);
	close(this->_sockserver);
}

void Server::sendMessage(std::string message) const
{
	message += "\r\n";
	if (send(this->_sockcom, message.c_str(), message.length(), 0) < 0)
		throw std::runtime_error("Error sending message.");
}

std::string Server::receiveMessage() const
{
	char buffer[1024];
	std::string message;
	memset(buffer, 0, 1024);

	if (recv(this->_sockcom, buffer, 1024, 0) < 0){
		std::cout << strerror(errno) << std::endl;
		throw std::runtime_error("Error receiving message");
	}
	message = buffer;
	return message;
}
