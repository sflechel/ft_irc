#include "Bot.hpp"
#include "Invite.hpp"
#include "PrivMsg.hpp"
#include <arpa/inet.h>
#include <csignal>
#include <cstddef>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

extern volatile sig_atomic_t g_signum;

Bot::Bot(int port, std::string password, std::string nickname)
    : _port(port), _password(password), _nickname(nickname) 
{
	struct sockaddr_in addr;
	const char *ip = "127.0.0.1";

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		throw std::runtime_error("Failed to create socket");

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(_port);
	if (connect(_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Failed to connect to server host");
}

void Bot::receivePacket(void) 
{
	char buffer[READ_BUFFER_SIZE + 1];
	int bytes_read = READ_BUFFER_SIZE;

	while (bytes_read == READ_BUFFER_SIZE)
	{
		bytes_read = recv(_socket, buffer, READ_BUFFER_SIZE, 0);
		if (bytes_read < 0)
			throw std::runtime_error("Disconnected from server host");
		buffer[bytes_read] = 0;
		_packet += std::string(buffer);
	}
}

void Bot::splitPacketToCmds(void)
{
	size_t cmd_start = 0;
	size_t cmd_end;

	_cmd_strings.erase(_cmd_strings.begin(), _cmd_strings.end());
	cmd_end = _packet.find("\r\n", cmd_start);
	while (cmd_end != std::string::npos)
	{
		std::string cmd = _packet.substr(cmd_start, cmd_end - cmd_start);
		if (!cmd.empty())
			_cmd_strings.push_back(cmd);
		cmd_start = cmd_end + 2;
		cmd_end = _packet.find("\r\n", cmd_start);
	}
	if (cmd_start != 0)
		_packet = _packet.substr(cmd_start, std::string::npos);
}

void Bot::parseCmdParams(std::string &input, std::string &sender, std::vector<std::string> &params)
{
	if (input.find(':') == 0) {
		size_t first_space = input.find(' ');
		if (first_space == std::string::npos)
			return;
		sender = input.substr(0, first_space);
		input = input.substr(first_space + 1, std::string::npos);
	}

	std::string last_param;
	bool has_last_param = false;
	size_t colon_pos = input.find(':');
	if (colon_pos != std::string::npos) {
		last_param = input.substr(colon_pos + 1, std::string::npos);
		input = input.substr(0, colon_pos);
		has_last_param = true;
	}

	std::stringstream ss(input);
	std::string param;

	while (getline(ss, param, ' '))
		if (!param.empty())
			params.push_back(param);
	if (has_last_param)
		params.push_back(last_param);
}

void Bot::execCmds(void) {
	for (size_t i = 0; i < _cmd_strings.size(); i++) {
		std::vector<std::string> params;
		std::string sender;
		parseCmdParams(_cmd_strings[i], sender, params);
		if (params.empty())
			continue;
		std::string cmd_name = params.at(0);
		params.erase(params.begin());

		Command *cmd = NULL;
		if (cmd_name == "PRIVMSG")
			cmd = new PrivMsg(_nickname, sender, cmd_name, params);
		else if (cmd_name == "INVITE")
			cmd = new Invite(_nickname, sender, cmd_name, params);
		else
			continue;
		_cmds.push_back(cmd);
	}

	for (size_t i = 0; i < _cmds.size(); i++)
		_cmds.at(i)->enactCommand(_socket);
	for (size_t i = 0; i < _cmds.size(); i++)
		delete _cmds.at(i);
	_cmds.erase(_cmds.begin(), _cmds.end());
}

void Bot::run(void) 
{
	std::string response = "PASS " + _password + "\r\n";
	response += "USER bot bot bot bot\r\n";
	response += "NICK " + _nickname + "\r\n";
	send(_socket, response.c_str(), response.size(), 0);
	this->receivePacket();
	std::cout << _packet << "\n";

	if (_packet.find("001") == std::string::npos)
		throw std::runtime_error("could not register to server");

	while (g_signum != SIGINT) {
		this->receivePacket();
		this->splitPacketToCmds();
		this->execCmds();
	}
}

std::string Bot::getNickname(void) const { return _nickname; }

std::string Bot::getPassword(void) const { return _password; }

Bot::~Bot(void) { close(_socket); }
