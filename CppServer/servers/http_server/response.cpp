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

std::string response::buildResponse(request& req)
{
	std::string buf;

	if (req.isGood())
	{
		auto path = req.header().path;
		buf = load_template_file(path);
	}
	else {
		buf = responses::code_to_html(status_code::bad_request);
	}
	return buf;
}


std::string response::load_template_file(std::string & path)
{
	std::vector<char> buf;
	std::string full_path;
	//construct a full path
	if (path == "/")
	{
		full_path = template_dir_ + "/greet.html";
	}
	else {
		full_path = template_dir_ + path + ".html";
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



