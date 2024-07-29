/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:54 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/29 16:31:45 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Channel_HPP
# define Channel_HPP

# include <string>
# include <vector>
# include "Client.hpp"

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::vector<Client*>	_operators;
		std::vector<Client*>	_clients;
		std::vector<Client*>	_invite;

		bool					_inviteOnly;
		long unsigned int		_userLimit;
		bool					_topicOperatorOnly;
		std::string				_password;

		Channel(void);

	public:
		Channel(std::string name, Client *client);
		~Channel();

		void		setName(std::string name);
		void		setTopic(std::string topic);
		void		setPassword(std::string password);
		void		addOperator(Client *newoperator);
		void		setInviteOnly(bool boolean);
		void		setUserLimit(long unsigned int limit);
		void		setTopicOperatorOnly(bool boolean);

		std::string				getName(void);
		std::string				getTopic(void);
		std::string				getPassword(void);
		std::vector<Client*>	&getClients(void);
		std::vector<Client*>	getOperators();
		std::vector<Client*>	&getInvite(void);
		std::string				getNames();
		bool					isOperator(Client *client);
		void					sendStr(std::string str);
		void					clientJoin(const std::string name, Client &client);
		bool					getInviteOnly();
		long unsigned int		getUserLimit();
		bool					getTopicOperatorOnly();
		void					sendMsg(Client &client, const std::string &message);

		int			inviteInChannel(Client &invitor, Client &invited,  Channel &channel);
		int			addClient(Client* client);
		void		delClient(Client* client);
		void		delClient(std::string &nick);
};


#endif
