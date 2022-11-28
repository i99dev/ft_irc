#include "../incl/Channel.hpp"

ft::Channel::Channel(Client *user, std::string &name)
{
	if (!this->_ChName_parse(name))
		throw WrongChannelNameRequir();
	else
		this->_name = name;
	this->_creator = user;
	_created_at = time(0);
	this->_topic = "";
	//it depends on how mant clients we can handle
	this->_max_clients = 255;
	this->_password = "";

}

void	ft::Channel::addClient(Client *user)
{
	this->_normal_clients.push_back(user);
}

std::string	ft::Channel::getChName(void)
{
	return (this->_name);
}

void	ft::Channel::sendMsgtoChannel(Message *message)
{
	(void)message;
}

ft::Channel::~Channel(){}
