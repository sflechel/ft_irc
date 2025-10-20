#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
	public:
		Client(int fd);
		~Client(void);

		int				getFd(void) const;
		void			setSentPassword(bool state);
		bool			getSentPassword(void) const;
		void			setIsRegistered(bool state);
		bool			getIsRegistered(void) const;
		void			setNickname(std::string nickname);
		std::string		getNickname(void) const;
		void			setUsername(std::string username);
		std::string		getUsername(void) const;
		std::string		getRequest(void) const;
		void			setRequest(std::string request);
		void			setRealname(std::string username);
		std::string		getRealname(void) const;
		void			setResponse(std::string response);
		std::string		getResponse(void) const;

	private:
		int				_fd;
		std::string		_request;
		std::string		_response;

		bool			_sent_password;
		bool			_is_registered;
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;

		Client(void)	{}
};

#endif // !CLIENT_HPP
