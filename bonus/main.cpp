/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:43:51 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/02 01:07:14 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "OpenaiReq.hpp"
#include <iostream>

int g_sig = 0;

int main(int argc, char **argv)
{
	OpenaiReq req("{\"apiKey\":\"sk-proj-m0cJ7UL5RcHqoAUDJ0BoT3BlbkFJlVahT9dx213Tf2QTmHGn\",\"messages\":[{\"role\":\"user\",\"content\":\"hello\"}]}");
	std::cout << req.send() << std::endl;
		
	//std::string ip;
	//std::string port;
	//std::string pass;

	//if(argc != 4)
	//{
	//	std::cerr << "wrong number of arguments" << std::endl;
	//	std::cerr << "	usage : " << argv[0] << " <ip> <port> <pass>" << std::endl;
	//	return(1);
	//}
	//signal(SIGINT, Handler);
	//signal(SIGPIPE, SIG_IGN);
	//ip = argv[1];
	//port = argv[2];
	//pass = argv[3];
	// try{
	//	
	//	Bot bot(ip, port);
	//	bot.login(pass);
	//	bot.listen();
	// }catch(std::exception &e)
	// {
	// 	std::cerr << e.what() << std::endl;
	// }
		
}
