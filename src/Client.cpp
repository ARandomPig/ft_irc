/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:05:52 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/25 15:55:53 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/*------------------------------- Constructors -------------------------------*/
Client::Client(int fd, Server &srv): _server(srv)
{
	_fd = fd;
	_user = "";
	_nick = "";
	_buffer = "";
	_loggedIn = false;
}

Client::~Client()
{
	close(_fd);
}

/*--------------------------------- Methods ----------------------------------*/
int	Client::updateBuffer()
{
	char buffer[1024];
	unsigned long len;

	std::cout << "new data form client " << this->_fd << std::endl;
	len = recv(this->_fd, buffer, 1024, MSG_DONTWAIT);
	if(!len || len == (unsigned long)-1)
		return (1);
	std::cout << "add" << std::endl;
	std::cout << "len : " << len << std::endl;
	this->_buffer += std::string(buffer, len);
	this->handleBuffer();
	return(0);
}

void	Client::handleBuffer()
{
	unsigned long len;
	std::string command;

	std::cout << "Buffer for client on fd " << this->_fd << " :" << std::endl;
	std::cout << this->_buffer << std::flush;
	while(_buffer.find('\n', 0) != std::string::npos) 
	{
		len = _buffer.find('\n', 0);
		_server.exec(_buffer.substr(0, len), *this);
		_buffer.erase(0, len + 1);
	}
}

int			Client::sendMessage(Client &from, std::string &to, std::string &message)
{
	if(!this->isRegistered())
		return(0);
	std::stringstream msg;
	msg << from.getNick() << "!" << from.getUser() << "@localhost ";
	msg << to << " :" << message << "\n";
	send(this->_fd, msg.str().c_str(), msg.str().length(),MSG_DONTWAIT);
	return(1);
}

int	Client::isRegistered()
{
	return(this->_loggedIn && this->_user.length() && this->_nick.length());
}

/*--------------------------------- Setters ----------------------------------*/
void	Client::setUser(std::string user)
{
	this->_user = user;
}
void	Client::setNick(std::string nick)
{
	this->_nick = nick;
}
void	Client::setLoggedIn(bool b)
{
	this->_loggedIn = b;
}

/*--------------------------------- Getters ----------------------------------*/
std::string	Client::getUser()
{
	return (this->_user);
}
std::string	Client::getNick()
{
	return (this->_nick);
}

int	Client::getFd()
{
	return(this->_fd);
}

std::string	Client::getBuffer()
{
	return (this->_buffer);
}

int Client::getLoggedIn()
{
	return(this->_loggedIn);
}
