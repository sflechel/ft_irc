#ifndef CHANNEL_HPP

# define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <string>

class Server;

class   Channel
{
    public:
        Channel(Server& server, std::string name, Client& user);
        ~Channel(void);
        void        addUser(std::string nickname);
        void        leave(std::string nickname);
        std::string getKey(void);
		bool		isUserOperator(const std::string &username) const;
		void		sendChannelMessage(const std::string& message, const Client& sender) const;
        std::string getTopic(void) const; 
        void        setTopic(std::string topic);
        std::string getName(void) const;
        std::set<std::string>&  getUsers(void);
        bool                    getIsUser(std::string nickname);
        bool                    getIsOp(std::string nickname);
        bool                    getIsInviteOnly(void);
        bool                    getIsTopicRestricted(void);
        int                     getUserLimit(void);
    private:
        std::string             _name;
        std::set<std::string>   _users;
        std::set<std::string>   _operators;
        std::string             _key;
        std::string             _topic;
		Server&					_server;
        int                     _user_limit;
        bool                    _is_invite_only;
        bool                    _is_topic_restricted;
};

#endif //CHANNEL_HPP
