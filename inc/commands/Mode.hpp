#ifndef MODE_HPP
# define MODE_HPP

#include "Command.hpp"
#include "Server.hpp"
#include <string>

class Mode : public Command
{
	public:
		Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Mode(void);

		void	enactCommand(void);

	private:
		bool	choseMode(void);
		bool	modeI(void);
		bool	modeO(void);
		bool	modeK(void);
		bool	modeL(void);
		bool	modeT(void);
		std::string			messageMode(void);
		char				_sign;
		char				_mode;
		Channel*			_channel;
};

#endif //MODE_HPP
