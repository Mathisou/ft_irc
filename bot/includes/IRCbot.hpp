#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <cstdlib>

class IRCbot
{
	private:

		std::string _name;
		std::set<std::string> _channels;

	public:

		IRCbot();
		virtual ~IRCbot();
		std::string & getName() const;
		std::string makeJoke();
		void addChannel(std::string channelName);
		
};