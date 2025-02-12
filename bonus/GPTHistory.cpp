/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GPTHistory.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:39:41 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/09 14:49:47 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GPTHistory.hpp"
#include "prompts.hpp"

GPTHistory::GPTHistory(std::string name) : _name(name) {}

void GPTHistory::addHistory(std::string role, std::string message)
{
    t_history history;
    
	message = replaceAll(message, "\\", "\\\\");
	message = replaceAll(message, "\"", "\\\"");
    history.role = role;
    history.message = message;
    _history.push_back(history);
}

std::string GPTHistory::getName() const
{
    return _name;
}

std::vector<t_history> GPTHistory::getHistory() const
{
    return _history;
}

GPTHistory &GPTHistory::operator=(const GPTHistory &other)
{
    _history = other.getHistory();
    return *this;
}

GPTHistory::~GPTHistory()
{
    for (unsigned int i = 0; i < _history.size(); i++)
	{
		_history[i].role.clear();
		_history[i].message.clear();
	}
}

std::string GPTHistory::getHistoryJson() const
{
	std::stringstream res;

	res << "[";
	res << "{\"role\":\"system\",\"content\":\"" SYSTEM_PROMPT "\"}";
	if(_history.size())
		res << ",";
	for(unsigned long i = 0;i < _history.size(); i++)
	{
		res << "{\"role\":\"" << _history[i].role << "\",";
		res << "\"content\":\"" << _history[i].message << "\"}";
		if(i != (_history.size() - 1))
			res << ",";
	}
	res << "]";
	std::cout << "res : " << res.str() << std::endl;
	return(res.str());
}
