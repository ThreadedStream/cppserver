#include "response.hpp"

namespace code_templates {
	std::string bad_req_template =
		"<h1 align=\"center\">Bad Request</h1>";

	std::string not_found_template =
		"<h1 align=\"center\">Not Found<h1>";
}

namespace responses {
	const char* code_to_html(response::status_code code)
	{
		switch (code) {
		case response::status_code::bad_request:
			return code_templates::bad_req_template.c_str();
			break;
		case response::status_code::not_found:
			return code_templates::not_found_template.c_str();
			break;
		default:
			return "Unknown code";
			break;
		}
	}
}

std::string response::handle_arithmetic(request& req)
{
	auto num1Str = req.header().req_data.at(0).value;
	auto num2Str = req.header().req_data.at(1).value;

	int num1 = atoi(num1Str.c_str());
	int num2 = atoi(num2Str.c_str());
	
	std::string buf;

	buf = "The result is " + std::to_string(num1 * num2);

	return buf;
}

std::string response::buildResponse(request& req)
{
	std::string buf;

	if (req.isGood())
	{
		buf = load_template_file(req);
	}
	else {
		buf = responses::code_to_html(status_code::bad_request);
	}
	return buf;
}


std::string response::load_template_file(request& req)
{
	auto path = req.header().path;
	std::vector<char> buf;
	std::string full_path;

	if (!req.header().req_data.empty())
	{
		return handle_arithmetic(req);
	}
	//construct a full path
	if (path == "/")
	{
		full_path = template_dir_ + "/" + "greet.html";
	}
	else {
		if (path.substr(path.length() - 4, path.length()) != ".css")
			full_path = template_dir_ + "/" + path + ".html";

		else {
			full_path = static_dir_ + '/' + path;
		}
	}
	std::ifstream in(full_path, std::ios::in | std::ios::binary);
	if (in.is_open())
	{	
		in.seekg(std::ios::beg, std::ios::end);
		size_t size = in.tellg();
		in.seekg(0);
		buf.resize(size);
		in.read(buf.data(), size);
		return buf.data();
	}
	else {
		std::string not_found_res = code_templates::not_found_template;
		return not_found_res.c_str();
	}
}
