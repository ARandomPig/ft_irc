/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:55:07 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 17:20:12 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"
#include "include.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "CommandManager.hpp"
#include <vector>
# include <iostream>
# include <sstream>

class Client;

class Server {
	private:
		int						_servSocketFd;
		std::string				_password;
		std::vector<Client*>	_client;

		int	init_socket(uint16_t port);

	public:
		Server(std::string port, std::string password); // Default constructor
		~Server(void);

		void		setServSocketFd(int servSocketFd);
		void		setPassword(std::string password);
		// void		setClient(Client client);

		int			getServSocketFd();
		std::string	getPassword();

		void		showClient(void);
		void		listen(void);
		void		addClient(int a);
		void		receiveData(void);

		class OutOfRangeClientExeption : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Index out of range";
				}
		};
};

#endif
