/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:36:14 by hubourge          #+#    #+#             */
/*   Updated: 2024/07/30 15:25:50 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int	pushInQueue(std::vector<std::string> &argSplit, std::queue<std::string> &modeQueue, Client &client);

// MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
// — i : Définir/supprimer le canal sur invitation uniquement
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal
void	commandMode(const std::string &arg, Client &client, Server &server)
{
	std::vector<void (*)(const std::string &, Client &, Server &, Channel &, std::string &, std::string &)>	functmode;
	std::vector<std::string>																				argSplit;
	std::queue<std::string>																					modeQueue;
	std::string																								allowedOption = "itkol";

	argSplit = ft_split(arg, ' ');
	if(argSplit.size() < 2)
	{
		client.sendInfo(0, 461, "MODE :Not enough parameters");
		return ;
	}
	if (server.getChannel(argSplit[0], 0) == 0)
	{
		client.sendInfo(0, 403, argSplit[0] + " :No such channel");
		return ;
	}
	Channel *channel = server.getChannel(argSplit[0], 0);
	if (pushInQueue(argSplit, modeQueue, client))
		return ;
	functmode.push_back(commandModeI);
	functmode.push_back(commandModeT);
	functmode.push_back(commandModeK);
	functmode.push_back(commandModeO);
	functmode.push_back(commandModeL);
	while (!modeQueue.empty())
	{
		std::string optionc = modeQueue.front();
		std::string arg = "";
		modeQueue.pop();
		for (size_t i = 0; i < optionc.length(); i++)
		{
			if (optionc[i] == '+' || optionc[i] == '-')
				continue ;
			if (allowedOption.find(optionc[i]) == std::string::npos)
			{
				client.sendInfo(0, 472, optionc + " :is unknown mode char to me for " + argSplit[0]);
				return ;
			}
			if (!modeQueue.empty() && arg.empty())
			{
				arg = modeQueue.front();
				modeQueue.pop();
			}
			functmode[allowedOption.find(optionc[i])](arg, client, server, *channel, optionc, arg);
		}
	}

}

/*--------------------------------- Options ----------------------------------*/
void	commandModeI(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	(void) cmdArg;
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		std::cout << "need more privilege" << std::endl;
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Channel mode is invite only");
		std::cout << "set mode invite only" << std::endl;
		chnl.setInviteOnly(true);
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Channel mode is not invite only");
		chnl.setInviteOnly(false);
		std::cout << "mode not invite only" << std::endl;

	}
}

void	commandModeT(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	(void) cmdArg;
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Channel mode is topic operator only");
		chnl.setTopicOperatorOnly(true);
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Channel mode is not topic operator only");
		chnl.setTopicOperatorOnly(false);
	}
}

void	commandModeK(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 0, ":Unset the channel key"); // trouver le bon code
		chnl.setPassword("");
	}
	else if (chnl.getPassword() != "")
	{
		client.sendInfo(0, 467, ":Channel key is already set");
		return ;
	}
	else if (cmdOpt[0] == '+')
	{
		if (cmdArg.empty())
		{
			client.sendInfo(0, 461, "MODE :Not enough parameters");
			return ;
		}
		client.sendInfo(0, 0, ":Set the channel key to " + cmdArg); // trouver le bon code
		chnl.setPassword(cmdArg);
		cmdArg.clear();
	}
}

void	commandModeO(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	(void) cmdArg;
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		client.sendInfo(0, 324, ":Channel mode is topic operator only");
		chnl.setTopicOperatorOnly(true);
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Channel mode is not topic operator only");
		chnl.setTopicOperatorOnly(false);
	}
}

void	commandModeL(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	if (chnl.isOperator(&client))
	{
		client.sendInfo(0, 482, "MODE :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		if (cmdArg.empty())
		{
			client.sendInfo(0, 461, "MODE :Not enough parameters");
			return ;
		}
		client.sendInfo(0, 324, ":Set the channel limit to " + arg);
		if (stdStringToLongUnsignedInt(cmdArg) > MAX_CHANNEL_USER)
			chnl.setUserLimit(MAX_CHANNEL_USER);
		else
			chnl.setUserLimit(stdStringToLongUnsignedInt(cmdArg));
		cmdArg.clear();
	}
	else if (cmdOpt[0] == '-')
	{
		client.sendInfo(0, 324, ":Unset the channel limit");
	}
}

/*---------------------------------- Utils -----------------------------------*/
bool verifOption(std::string option)
{
	std::string		allowedOption = "+-itkol";
	for (size_t i = 0; i < option.length(); i++)
	{
		if (allowedOption.find(option[i]) == std::string::npos)
			return false;
	}
	return true;
}

int	pushInQueue(std::vector<std::string> &argSplit, std::queue<std::string> &modeQueue, Client &client)
{
	for (unsigned int i = 1; i < argSplit.size(); i++)
	{
		if (argSplit[i][0] == '+' || argSplit[i][0] == '-')
		{
			if (verifOption(argSplit[i]))
			{
				modeQueue.push(argSplit[i]);
				std::cout << "option: " << argSplit[i] << std::endl;
			}
			else
			{
				client.sendInfo(0, 472, argSplit[i] + " :is unknown mode char to me for " + argSplit[0]);
				return 1;
			}
		}
		else
			modeQueue.push(argSplit[i]);
	}
	return 0;
}
