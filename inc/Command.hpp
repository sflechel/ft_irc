#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

class Command
{
	public:
		Command();
		Command(std::string cmd_str);
		~Command();

		void	parse_cmd();
		bool	is_valid_cmd();

	private:
		std::string					_cmd_str;
		std::string					_cmd;
		std::vector<std::string>	_params;

		void parse_params();
};

#endif
