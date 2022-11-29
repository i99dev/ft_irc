#include "../incl/Channel.hpp"

// ft::Channel::Channel(Client *user, std::string &name)
// {
// 	if (!this->_ChName_parse(name))
// 		throw WrongChannelNameRequir();
// 	else
// 		this->_name = name;
// 	this->_creator = user;
// 	_created_at = time(0);
// 	this->_topic = "";
// 	//it depends on how mant clients we can handle
// 	this->_max_clients = 255;
// 	this->_password = "";

// }

ft::Channel::Channel(std::string &name, std::string &password)
{

	this->_name = name;
	this->_creator = NULL;
	_created_at = time(0);
	this->_topic = "";
	//it depends on how mant clients we can handle
	this->_max_clients = 255;
	this->_password = password;

	std::cout << "Channel " << this->_name << " created" << std::endl;
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

//get password
std::string	&ft::Channel::getPassword()
{
	return (this->_password);
}

ft::Channel::~Channel(){}
