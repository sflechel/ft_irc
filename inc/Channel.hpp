#ifndef CHANNEL_HPP

# define CHANNEL_HPP

#include "Client.hpp"
#include <set>
#include <string>

class   Channel
{
    public:
        Channel(std::string name, Client& user);
        ~Channel(void);
        void        addUser(std::string nickname);
        void        leave(std::string nickname);
        std::string getKey(void);
    private:
        std::string             _name;
        std::set<std::string>   _users;
        std::set<std::string>   _operators;
        std::string             _key;
        std::string             _topic;
        int                     _user_limit;
        bool                    _is_invite_only;
        bool                    _is_topic_restricted;
};

#endif //CHANNEL_HPP
