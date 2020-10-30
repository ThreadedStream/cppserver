#include "connection.hpp"




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

void connection::initDBConnection(err_code& err)
{
	if (!connInstance->init_conn())
	{
		err.cause = "Failed to initialize connection to a database\n";
	}
}
	
//Main(so-called "driver") method
void connection::start_processing()
{
	Logger::log(SEVERITY::DEBUG, "Preparation of necessary resources\n");
	Logger::log(SEVERITY::DEBUG, "Attempt to initialize database connection\n");
	err_code err;
	initDBConnection(err);
	if (err.cause == "")
	{
		Logger::log(SEVERITY::DEBUG, "Database connection has been successfully established");
	}
	else {
		Logger::log(SEVERITY::ERR, err.cause);
	}
	
	
	auto self(shared_from_this());
	//load_file(FILENAME);
	socket_.async_read_some(buffer(buffer_), [&, self](const errc& err, size_t length) {
		if (!err)
		{
			Logger::log(SEVERITY::DEBUG, "Message: " + std::string(buffer_.c_array()));
			request req(buffer_.c_array());
			std::string str = resp.buildResponse(req);


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