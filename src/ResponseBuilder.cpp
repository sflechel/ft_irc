#include "ResponseBuilder.hpp"
#include "Client.hpp"
#include <sstream>
#include <string>
#include <cstdlib>

ResponseBuilder::ResponseBuilder(std::string& servername, e_numeric numeric, Client& target) : _servername(servername), _numeric(numeric), _target(target)
{}

ResponseBuilder::~ResponseBuilder(void) {}

std::string enummericToString(e_numeric code)
{
    std::stringstream   output;

    if (code / 10 < 10)
        output << "00" << (int)code;
    else if (code / 100 < 10)
        output << "0" << (int)code;
    else
        output << (int)code;
    return (output.str());
}

std::string ResponseBuilder::buildResponseString(void)
{
    std::stringstream response;

    response << (":" + this->_servername + " ");
    response << enummericToString(this->_numeric) << " ";
    response << this->_target.getNickname();
    response << "\r\n";
    return (response.str());
}
