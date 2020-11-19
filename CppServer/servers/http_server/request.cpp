#include "request.hpp"


namespace valid_data {

	std::unordered_set<std::string> methods = {
		"GET", "POST", "PUT", "DELETE", "HEAD" 
	};
}
/*
*/
void request::parseRequestData(const std::string& path)
{
	auto found = path.find_first_of("?");
	if (found == path.npos)
	{
		return;
	}

	auto data_part = path.substr(found + 1);
	
	//Chopping off the request data out of a path
	req_header_.path = path.substr(0, found);

	request_data field_val;

	int i = 0;
	while (i < data_part.length())
	{
		if (data_part[i] == '&')
		{
			req_header_.req_data.push_back(field_val);
			field_val.key = "";
			field_val.value = "";
			i++;
		}
		
		while (data_part[i] != '=')
		{
			field_val.key += data_part[i];
			i++;
		}
		i++;
		while (i < data_part.length() && data_part[i] != '&')
		{
			field_val.value += data_part[i];
			i++;
		}
	}

	if (i == data_part.length() && field_val.key != "" && field_val.value != "")
	{
		req_header_.req_data.emplace_back(field_val);
	}
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

	parseRequestData(req_header_.path);

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
