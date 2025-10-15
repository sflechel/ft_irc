#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
	public:
		Client(int fd);
		~Client(void);

		int				get_my_fd(void) const;
        std::string     getNickname(void) const;
        std::string     getUsername(void) const;
        std::string     getResponse(void) const;
        void            setResponse(std::string response);
        std::string     getDataReceived(void) const;
        void            setDataReceived(std::string data);
	private:
		int				_my_fd;
        std::string     _data_received;
        std::string     _response;

		bool			_is_registered;
		std::string		_nickname;
		std::string		_username;

		Client(void)	{}
};

#endif // !CLIENT_HPP
