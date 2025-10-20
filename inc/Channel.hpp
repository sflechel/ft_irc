#ifndef CHANNEL_HPP

# define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <string>

class Server;

class Channel
{
	public:
		Channel(Server& server, std::string name, Client& user);
		~Channel(void);

		void	addUser(std::string nickname);
		void	leave(std::string nickname);
		bool	isUserOperator(const std::string &username) const;
		void	sendChannelMessage(const std::string& message, const Client& sender) const;

		void					setIsInviteOnly(const bool flag);
		void					setIsTopicRestricted(const bool flag);
		void					setKey(const std::string& str);
		void					setUserLimit(const int limit);
		void					setTopic(std::string topic);

		bool					getIsInviteOnly(void) const;
		std::string				getTopic(void) const;
		std::string				getKey(void) const;
		std::string				getName(void) const;
		int						getUserLimit(void) const;
		std::set<std::string>&	getUsers(void);
		bool					getIsUser(std::string nickname);
		bool					getIsOp(std::string nickname);
		bool					getIsTopicRestricted(void);

	private:
		std::string			 _name;
		std::set<std::string>	_users;
		std::set<std::string>	_operators;
		std::string				_key;
		std::string				_topic;
		Server&					_server;
		int						_user_limit;
		bool					_is_invite_only;
		bool					_is_topic_restricted;
};

#endif //CHANNEL_HPP
