#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
	public:
		Client(int fd);
		~Client();

		int				get_my_fd();

	private:
		int				_my_fd;
		bool			_is_registered;
		std::string		_nickname;
		std::string		_username;
        std::string     _response;
		Client(void)	{}
};

#endif // !CLIENT_HPP
