#ifndef MODE_HPP
# define MODE_HPP

#include "Command.hpp"
#include "Server.hpp"

class Mode : public Command
{
	public:
		Mode(Server& server, Client& user, std::string cmd_name, std::vector<std::string> params);
		~Mode(void);

		void	enactCommand(void);

	private:
		void	choseMode(void);
		void	ModeI(void);
		void	ModeO(void);
		void	ModeK(void);
		void	ModeL(void);
		void	ModeT(void);
		char				_sign;
		char				_mode;
		Channel*			_channel;
};

#endif //MODE_HPP
