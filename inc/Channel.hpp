#ifndef CHANNEL_HPP

# define CHANNEL_HPP

#include "Client.hpp"
#include <string>
#include <vector>

class   Channel
{
    public:
        Channel(Client& user);
        ~Channel(void);
    private:
        std::string             _name;
        std::vector<Client*>    _users;
        std::vector<Client*>    _operators;
        std::string             _key;
        std::string             _topic;
        int                     _user_limit;
        bool                    _is_invite_only;
        bool                    _is_topic_restricted;
};

#endif //CHANNEL_HPP
