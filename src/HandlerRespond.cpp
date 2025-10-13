#include "HandlerRespond.hpp"
#include <cerrno>
#include <sys/socket.h>

HandlerRespond::HandlerRespond(Client& client) : _client(client)
{}

HandlerRespond::~HandlerRespond()
{}
