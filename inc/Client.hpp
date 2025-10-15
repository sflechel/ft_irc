#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Command.hpp"
# include <string>

class Client
{
	public:
		Client(int fd);
		~Client(void);

		int				get_my_fd(void) const;
        std::string     getNickname(void) const;
        std::string     getResponse(void) const;
        void            setResponse(std::string response);
        //COMMANDS
        void            Pass(Command& command, std::string& password);
	private:
		int				_my_fd;
		bool			_is_registered;
		std::string		_nickname;
		std::string		_username;
        std::string     _response;
		Client(void)	{}
};

#endif // !CLIENT_HPP
