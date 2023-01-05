#include "Client.cpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw std::runtime_error("Usage: ./ircclient <port> <password>");
		client client(av[1], av[2]);
		// client.sendMessage("lol");
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		std::cout << strerror(errno) << std::endl;
		return 1;
	}
}