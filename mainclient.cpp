#include "Client.cpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw std::runtime_error("Usage: ./ircclient <port> <password>");
		client client(av[1], av[2]);
		std::string pswd;
		std::cout << client.receiveMessage() << std::endl;
		std::cin >> pswd;
		client.verifpswd(pswd);
		// client.sendMessage(pswd);
		// std::cout << client.receiveMessage() << std::endl;
		// std::cout << "test" << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		std::cout << strerror(errno) << std::endl;
		return 1;
	}
}