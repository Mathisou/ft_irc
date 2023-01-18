#ifndef USER_HPP
# define USER_HPP

#include "main.hpp"

class User{
	private:
	std::string _nickname;
	std::string _username;
	std::string _hostname;
	std::string _real_name;
	std::vector<std::string> _channels;
	// bool _is_connect;
	// bool _is_oper;

	public:
	User(std::string nick, std::string user, std::string hostname, std::string real_name);
	User(const User &T);
    User &operator=(const User &T);
	~User();
	std::string getNickname() const;
	std::string getUsername() const;
	std::string getHostname() const;
	std::string getReal_name() const;
	std::vector<std::string> getChannels() const;
	void add_channel(std::string channel_name);
	void setNick(std::string new_nickname);
	// bool getIs_oper() const;

};

#endif
