#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

class Command
{
	public:
		Command(std::string cmd_str);
		~Command(void);

		void	parse_cmd(void);
		bool	is_valid_cmd(void);
        virtual void    enactCommand(void) = 0;
	private:
		std::string					_cmd_str;
		std::string					_cmd;
		std::vector<std::string>	_params;

		void parse_params(void);

		Command(void);
};

#endif
