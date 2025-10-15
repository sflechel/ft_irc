#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
	public:
		Client(int fd);
		~Client(void);

		int				getMyFd(void) const;
		void		    setIsRegistered(bool state);
		bool		    getIsRegistered(void) const;
        void            setNickname(std::string nickname);
        std::string     getNickname(void) const;
        void            setUsername(std::string username);
        std::string     getUsername(void) const;
        void            setResponse(std::string response);
        std::string     getResponse(void) const;
        void            setDataReceived(std::string data);
        std::string     getDataReceived(void) const;
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
