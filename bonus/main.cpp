/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:43:51 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/31 14:07:24 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <iostream>

int g_sig = 0;

int main(int argc, char **argv)
{
	std::string ip;
	std::string port;
	std::string pass;

	if(argc != 4)
	{
		std::cerr << "wrong number of arguments" << std::endl;
		std::cerr << "	usage : " << argv[0] << " <ip> <port> <pass>" << std::endl;
		return(1);
	}
	ip = argv[1];
	port = argv[2];
	pass = argv[3];
	try{
		Bot bot(ip, port);
		while(1)
		{
		
		}
		//bot.login(pass)
		//bot.listen();
	}catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
		
}
