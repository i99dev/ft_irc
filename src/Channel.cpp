#include "../incl/Channel.hpp"

ft::Channel::Channel(std::string &name,  std::string &password): _name(name), _password(password), _max_clients(255), _creator(NULL) {
	_created_at = time(0);
}

ft::Channel::Channel(/* args */)
{
}

ft::Channel::~Channel()
{
}
