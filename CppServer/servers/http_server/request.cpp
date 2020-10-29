#include "request.hpp"


namespace valid_data {

	std::unordered_set<std::string> methods = {
		"GET", "POST", "PUT", "DELETE", "HEAD" 
	};
}

void request::parse()
{
	int i = 0;
	char currC = 0;
	//parsing request method
	while (req_str_[i] != ' ')
	{
		currC = req_str_[i];
		req_header_.method += currC;
		i++;
	}
	i++;

	//parsing path
	while (req_str_[i] != ' ')
	{
		currC = req_str_[i];
		req_header_.path += currC;
		i++;
	}
	i++;
	
	//parsing protocol;
	while (req_str_[i] != '/')
	{
		currC = req_str_[i];
		req_header_.protocol += currC;
		i++;
	}
	i++;

	req_header_.majVer = req_str_[i] - '0';
	req_header_.minVer = req_str_[i + 2] - '0';
}


bool request::isGood()
{
	parse();
	if (valid_data::methods.find(req_header_.method.c_str()) != valid_data::methods.end()
		&& req_header_.protocol == "HTTP")
	{
		return true;
	}
	
	else {
		Logger::log(SEVERITY::DEBUG, std::to_string(valid_data::methods.find(req_header_.method.c_str()) != valid_data::methods.end()));
		Logger::log(SEVERITY::DEBUG, std::to_string(req_header_.protocol == "HTTP"));
		return false;
	}
}


void request::consume(char c)
{
}
