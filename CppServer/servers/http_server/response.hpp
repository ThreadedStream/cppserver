#pragma once
#include "../../core/typedefs.hpp"
#include "../../core/header.hpp"
#include "request.hpp"

class response {
public:
	enum class status_code {
		ok = 200,
		created = 201,
		accepted = 202,
		no_content = 204,
		multiple_choices = 300,
		moved_permanently = 301,
		moved_temporarily = 302,
		not_modified = 304,
		bad_request = 400,
		unauthorized = 401,
		forbidden = 403,
		not_found = 404,
		internal_server_error = 500,
		not_implemented = 501,
		bad_gateway = 502,
		service_unavailable = 503
	}code;

	explicit response(const std::string& template_dir):
					template_dir_(template_dir)
					{};

	std::string buildResponse(request& req);

	inline std::string response_content() const noexcept{ return content; } 
	

private:
	std::string load_template_file(std::string& path);

private:
	std::string content;
	std::string template_dir_;
	//std::vector<const_buffer> to_buffers();
	//static response stock_response(status_code status);

};