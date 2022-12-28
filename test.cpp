/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:31:16 by aaljaber          #+#    #+#             */
/*   Updated: 2022/12/28 15:26:27 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

class Client
{
	private:
		/* data */
	public:
		int	data;
		Client(/* args */);
		void	setData(int data);
		~Client();
};

void	Client::setData(int data)
{
	this->data = data;
}


Client::Client(/* args */):data(0){}

Client::~Client(){}

struct member
{
	Client *user;
};


int main ()
{
	Client *user1 = new Client();

	std::vector<Client *> clients;
	std::vector<Client *> clients1;
	clients.push_back(user1);

	std::cout << "first initialize from clients vector " << clients[0]->data << std::endl;

	struct member member1;
	member1.user = user1;

	std::vector<struct member> members;
	members.push_back(member1);

	std::cout << "first initialize from member vector  " << members[0].user->data << std::endl;
	std::cout << std::endl;

	user1->data = 2;
	std::cout << "change data to " << user1->data << std::endl;
	std::cout << "check data change from clients vector " << clients[0]->data << std::endl;
	std::cout << "check data change from members vector  " << members[0].user->data << std::endl;

	clients1 = clients;
	std::cout << "first initialize from clients1 vector  " << clients1[0]->data << std::endl;
	std::cout << std::endl;

	clients[0]->data = 3;

	std::cout << "change data from clients vector to " << clients[0]->data << std::endl;
	std::cout << "check data change from members vector  " << members[0].user->data << std::endl;
	std::cout << "check data change from clients1 vector  " << clients1[0]->data << std::endl;
	std::cout << std::endl;


	clients[0]->setData(4);
	std::cout << "change data from setter " << user1->data << std::endl;
	std::cout << "check setter change from clients vector " << clients[0]->data << std::endl;
	std::cout << "check setter change from members vector  " << members[0].user->data << std::endl;
	std::cout << "check setter change from clients1 vector  " << clients1[0]->data << std::endl;


}
