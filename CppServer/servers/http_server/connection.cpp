#include "connection.hpp"



connection::connection(asio_ctx& context) :
	socket_(context)
{
	stx.set_template_dir("templates");
	stx.set_req_file("dblog.txt");
	stx.set_static_dir("static");
	resp.set_template_dir(stx.template_dir());
	resp.set_static_dir(stx.static_dir());
}

void connection::load_file(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::in);
	
	if (boost::filesystem::exists(filename))
	{
		stream.seekg(0, std::ios::end);
		size_t size = stream.tellg();
		stream.seekg(std::ios::beg);
		stream.read(buffer_.data(), size);
	}
	else
	{
		Logger::log(SEVERITY::ERR, "File does not exist\n");
	}
}

void connection::request_db(const std::string& msg, err_code& err)
{
	if (dbwriter.is_open())
	{
		auto date = _now();
		auto whole_message = msg + date;
		dbwriter.write(whole_message.c_str(), msg.length());
	}
	else {
		err.cause = "Failed to open db log file\n";
		return;
	}
}

/*
	@Function for obtaining current time
*/
std::string connection::_now()
{
	time_t raw_time;
	struct tm * timeinfo = (struct tm*) malloc(sizeof(struct tm));
	char buffer[80];

	time(&raw_time);

	localtime_s(timeinfo, &raw_time);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);

	delete timeinfo;

	std::string output = "\n";
	output += buffer;

	return output;
}

//Main(so-called "driver") method
void connection::start_processing()
{
	Logger::log(SEVERITY::DEBUG, "Preparation of necessary resources\n");
	Logger::log(SEVERITY::DEBUG, "Attempt to initialize database connection\n");
	
	auto self(shared_from_this());
	//load_file(FILENAME);
	socket_.async_read_some(buffer(buffer_), [&, self](const errc& err, size_t length) {
		if (!err)
		{
			Logger::log(SEVERITY::DEBUG, "Message: " + std::string(buffer_.c_array()));
			err_code err_c;
			request_db(buffer_.data(), err_c);
			if (err_c.cause != "")
			{
				Logger::log(SEVERITY::DEBUG, err_c.cause);
			}
			else {
				Logger::log(SEVERITY::DEBUG, "Headers are written to a file\n");
			}
			request req(buffer_.c_array());
			std::string str;
			
			str = resp.buildResponse(req);

			for (auto& ch : str)
			{
				if (isascii(ch))
				{
					response_string += ch;
				}
			}

			socket_.async_write_some(buffer(response_string), [&, self](const errc& err, size_t length) {
				if (err) {
					Logger::log(SEVERITY::ERR, err.message());
				}
				else {
					Logger::log(SEVERITY::DEBUG, "Number of bytes sent: " + length + std::string("\n"));
					/*socket_.async_read_some(buffer(buffer_), boost::bind(&connection::read_completion_handler,
						shared_from_this(),
						placeholders::error,
						placeholders::bytes_transferred));*/
				}
			});
		}
		else {
			Logger::log(SEVERITY::ERR, err.message());
		}
	});
}

void connection::write_completion_handler(const errc & err, size_t bytes_transferred)
{
		
}

void connection::read_completion_handler(const	errc & err, size_t bytes_transferred)
{
	
}