#include "../incl/Channel.hpp"

ft::Channel::Channel(std::string &name,  std::string &password): _password(password), _max_clients(255), _creator(NULL) 
{
	if (!this->_ChName_parse(std::string &name)
		throw Channel::WrongChannelNameRequir();
	_created_at = time(0);
}

ft::Channel::~Channel()
{
}

