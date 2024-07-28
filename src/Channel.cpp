/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:42:37 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/28 15:54:48 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/*------------------------------- Constructors -------------------------------*/
Channel::Channel(void)
{
}

Channel::Channel(std::string name, Client *client) : _name(name)
{
	this->_topic = "";
	this->_password = "";
	this->_userLimit = 1000;
	this->_operators.push_back(client);
	this->_clients.push_back(client);
	this->_inviteOnly = false;
	this->_topicOperatorOnly = false;
}

Channel::~Channel(void)
{
}

/*--------------------------------- Methods ----------------------------------*/
int	Channel::addClient(Client* client)
{
	if (_clients.size() > this->_userLimit)
	{
		client->sendInfo(0, 471, this->_name + " :Cannot join channel (+l)");
		return(0);
	}
	if(std::find(this->_clients.begin(), this->_clients.end(), client) == this->_clients.end())
		this->_clients.push_back(client);
	return(1);
}

void	Channel::delClient(std::string nick)
{
	for (unsigned int i = 0; i < this->_clients.size() - 1; i++)
	{
		if (this->_clients[i]->getNick() == nick)
			this->_clients.erase(this->_clients.begin() + i);
	}
}

int	Channel::inviteInChannel(Client &invitor,	Client &invited,  Channel &channel)
{
	if (!isOperator(&invitor))
	{
		invitor.sendInfo(0, 482, ":You're not channel operator");
	}
	channel.getInvite().push_back(&invited);
	return (0);
}

bool Channel::isOperator(Client *client)
{
	return(std::find(this->_operators.begin(), this->_operators.end(), client) != this->_clients.end());
}

std::string Channel::getNames()
{
	std::string res;

	res = "";
	for(unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if(std::find(this->_operators.begin(), this->_operators.end(), this->_clients[i]) != this->_operators.end())
			res += "@";
		res += this->_clients[i]->getNick();
		if(i != this->_clients.size() - 1)
			res += " ";
	}
	return(res);
}

void Channel::sendStr(std::string str)
{
	for(unsigned long i = 0; i < _clients.size(); i++)
		_clients[i]->sendStr(str);
}

void		Channel::clientJoin(const std::string name, Client &client)
{
	std::string msg;

	msg = ":" + client.getIdentifier() + " JOIN " + name;
	this->sendStr(msg);
}

void		Channel::sendMsg(Client &client, const std::string &message)
{
	for(unsigned long i = 0; i < _clients.size(); i++)
		if(&client != _clients[i])
			_clients[i]->sendMsg(client, this->_name, message);
}

/*--------------------------------- Getters ----------------------------------*/

std::string Channel::getName(void)
{
	return this->_name;
}

std::string Channel::getTopic(void)
{
	return this->_topic;
}

std::string Channel::getPassword(void)
{
	return this->_password;
}

std::vector<Client*> &Channel::getClients(void)
{
	return this->_clients;
}

std::vector<Client*> Channel::getOperators()
{
	return this->_operators;
}

std::vector<Client*> &Channel::getInvite(void)
{
	return this->_invite;
}

bool Channel::getInviteOnly(void)
{
	return (this->_inviteOnly);
}

long unsigned int Channel::getUserLimit(void)
{
	return (this->_userLimit);
}

bool Channel::getTopicOperatorOnly(void)
{
	return (this->_topicOperatorOnly);
}

/*--------------------------------- Setters ----------------------------------*/
void	Channel::setName(std::string name)
{
	this->_name = name;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void	Channel::setPassword(std::string password)
{
	this->_password = password;
}

void Channel::addOperator(Client *newoperator)
{
	this->_operators.push_back(newoperator);
}

void Channel::setInviteOnly(bool boolean)
{
	this->_inviteOnly = boolean;
}

void Channel::setUserLimit(long unsigned int limit)
{
	this->_userLimit = limit;
}

void Channel::setTopicOperatorOnly(bool boolean)
{
	this->_topicOperatorOnly = boolean;
}
