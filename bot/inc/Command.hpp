#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

class Command
{
	public:
		Command(std::string nickname, std::string sender, std::string cmd_name, std::vector<std::string> params);
		virtual ~Command(void);

		virtual void	enactCommand(int socket) = 0;
	protected:
		std::string					_nickname;
		std::string					_sender;
		std::string					_cmd_name;
		std::vector<std::string>	_params;
};

#endif
