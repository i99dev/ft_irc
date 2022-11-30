#ifndef PRIVMSG_HPP

#define PRIVMSG_HPP

#include "./Command.hpp"

namespace ft{
	class Privmsg: public ft::Command{
		public:
			Privmsg();
			void	execute();

	};
}

#endif
