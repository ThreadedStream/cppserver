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
		boost::thread post_req_thread(boost::bind(&response::handle_post_request, this, req));
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


std::string response::handle_post_request(request& req)
{
	auto host = "127.0.0.1";
	auto port = 5600;
	endp_obj db_endp(ADDR_FROM_STR(host), 5600);

	//request_stream << json;

	asio_ctx ctx;
	sock_t sock_(ctx);
	sock_.connect(db_endp);
	auto hostname = "127.0.0.1";

	std::string request_buffer;
	std::ostringstream buf;

	ptree root;

	write_json(buf, root, false);

	std::string json = buf.str();

	request_buffer += "GET / HTTP/1.1\r\n";
	request_buffer += "Content-Type: text/plain; charset=utf-8 \r\n";
	request_buffer += "Accept: */*\r\n";
	request_buffer += "Connection: close\r\n\r\n";

	err_code err;
	sync_client{ sock_ptr_t(&sock_), request_buffer }(err);
	if (err.cause != "") {
		Logger::log(SEVERITY::ERR, err.cause);
		return "";
	}

	//root.put("first_name", "Jerry");
	//root.put("last_name", "Freed");
	//root.put("email", "jerry.freed@gmail.com");
	//root.put("password", "1234");
	
	return "Je'm balade sur l'avenue";
}

void response::connect_handler(const errc & err_conn)
{
	
}


void response::write_handler(const errc & err, size_t bytes)
{
	if (!err)
	{
		async_read(sock,resp, boost::bind(&response::read_handler, this,
											placeholders::error, placeholders::bytes_transferred));
	}
	else {
		std::cerr << err.value();
	}
}

	
void response::read_handler(const errc & err, size_t bytes)
{
	if (!err)
	{
		std::string resp_str((std::istreambuf_iterator<char>(&resp)), std::istreambuf_iterator<char>());

		std::cout << resp_str;
	}
	else {
		std::cout << err.value();
	}
}
