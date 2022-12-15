#include "Bot.hpp"

std::string create(std::string &msgRecv, std::string &toSend, std::string &sender){
	int i = 0;
	std::string tmp = "";
	if ((msgRecv.find("create")) != std::string::npos){
		i = msgRecv.find("create");
		i += 6;
		while (msgRecv[i] == ' ')
			i++;
		int j = 0;
		if (msgRecv[i] != '#' && msgRecv[i] != '&'){
			j++;
			tmp += "#";
		}
		while (msgRecv[i] != ' ' && msgRecv[i]){
			j++;
			tmp += msgRecv[i++];
		}
		if (j <= 1)
			return toSend;
		std::cout << "\033[0;34m" << "channel " << tmp << " has been created" << std::endl;
		std::cout << "\033[0;34m" << sender << " has been invited" << std::endl;
		return toSend + "JOIN " + tmp + "\r\n" + "INVITE " + sender + " " + tmp;
	}
	return toSend;
}

std::string shout(std::string &msgRecv, std::string &toSend, std::string &sender){
	int i = 0;
	(void)sender;
	std::string tmp = "";
	std::string tmp2 = "";
	if ((msgRecv.find("shout")) != std::string::npos){
		i = msgRecv.find("shout");
		i += 5;
		while (msgRecv[i] == ' ')
			i++;
		int j = 0;
		if (msgRecv[i] != '#' && msgRecv[i] != '&')
			return toSend;
		while (msgRecv[i] != ' ' && msgRecv[i]){
			j++;
			tmp += msgRecv[i++];
		}
		if (j == 0)
			return toSend;
		while (msgRecv[i] == ' ')
			i++;
		j = 0;
		while (msgRecv[i] != ';' && msgRecv[i]){
			j++;
			tmp2 += msgRecv[i++];
		}
		if (j == 0)
			return toSend;
		std::cout << "\033[0;34m" << "msg has successfully been sent anonymously" << std::endl;
		return toSend + "PRIVMSG " + tmp + " :" + tmp2;
	}
	return toSend;
}

std::string invite(std::string &msgRecv, std::string &toSend, std::string &sender){
	int i = 0;
	(void)sender;
	std::string tmp = "";
	std::string tmp2 = "";
	if ((msgRecv.find("invite")) != std::string::npos){
		i = msgRecv.find("invite");
		i += 6;
		while (msgRecv[i] == ' ')
			i++;
		int j = 0;
		while (msgRecv[i] != ' ' && msgRecv[i]){
			j++;
			tmp += msgRecv[i++];
		}
		if (j == 0)
			return toSend;
		while (msgRecv[i] == ' ')
			i++;
		j = 0;
		while (msgRecv[i] != ' ' && msgRecv[i]){
			j++;
			tmp2 += msgRecv[i++];
		}
		if (j == 0)
			return toSend;
		std::cout << "\033[0;34m" << tmp2 << " has been invited successfully" << std::endl;
		return toSend + "INVITE " + tmp + " " + tmp2;
	}
	return toSend;
}

std::string help(std::string &msgRecv, std::string &toSend, std::string &format){
	if (msgRecv.find("help") != std::string::npos){
		std::cout << "\033[0;33m" << "Help was called" << std::endl;
		return toSend + HELP(format);
	}
	return toSend;
}

std::string ehelp(std::string &msgRecv, std::string &toSend, std::string &format){
	if (msgRecv.find("ehelp") != std::string::npos){
		std::cout << "\033[0;33m" << "Help was called" << std::endl;
		return toSend + EHELP(format);
	}
	return toSend;
}

std::string commands(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("commands") != std::string::npos && (msgRecv.find("tell") != std::string::npos || msgRecv.find("available") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + CMDLIST(format);
	}
	return toSend;
}

std::string greeting(std::string &msgRecv, std::string &toSend, std::string &format){
	if (msgRecv.find("hello") != std::string::npos ||
		msgRecv.find("hey") != std::string::npos ||
		msgRecv.find("hi") != std::string::npos){
		std::cout << "\033[0;36m" << "greeting was sent" << std::endl;
		return toSend + WLCM(format);
	}
	return toSend;
}

std::string syntaxUser(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("user") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + USER(format);
	}
	return toSend;
}

std::string syntaxNick(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("nick") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + NICK(format);
	}
	return toSend;
}

std::string syntaxPing(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("ping") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + PING(format);
	}
	return toSend;
}

std::string syntaxQuit(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("quit") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + QUIT(format);
	}
	return toSend;
}

std::string syntaxKill(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("kill") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + KILL(format);
	}
	return toSend;
}

std::string syntaxJoin(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("join") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + JOIN(format);
	}
	return toSend;
}

std::string syntaxPart(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("part") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + PART(format);
	}
	return toSend;
}

std::string syntaxPrivmsg(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("privmsg") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + PRIVMSG(format);
	}
	return toSend;
}

std::string syntaxNotice(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("notice") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + NOTICE(format);
	}
	return toSend;
}

std::string syntaxInvite(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("invite") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + INVITE(format);
	}
	return toSend;
}

std::string syntaxKick(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("kick") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + KICK(format);
	}
	return toSend;
}

std::string syntaxTopic(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("topic") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + TOPIC(format);
	}
	return toSend;
}

std::string syntaxMode(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("mode") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + MODE(format);
	}
	return toSend;
}

std::string syntaxWhois(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("whois") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + WHOIS(format);
	}
	return toSend;
}

std::string syntaxList(std::string &msgRecv, std::string &toSend, std::string &format){
	if ((msgRecv.find("syntax") != std::string::npos && (msgRecv.find("list") != std::string::npos))){
		std::cout << "\033[0;35m" << "command help was called" << std::endl;
		return toSend + LIST(format);
	}
	return toSend;
}