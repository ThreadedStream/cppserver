#pragma once
#include "../../core/logger.hpp"
#include "../../core/non_copyable.hpp"
#include "response.hpp"

//NOTE: Temporary declarations
#define FILENAME_DEMO "F:/demo.cpp"
#define FILENAME "index.html"
#define TEMPLATE_DIR "G:/cppserver/CppServer/CppServer/templates/"


class connection : 
	public boost::enable_shared_from_this<connection>,
	private non_copyable
{
public:
	explicit connection(asio_ctx& context) :
		//strand_(make_strand(context)),
		socket_(context),
		//Note that trailing slash is required for proper functioning
		resp(TEMPLATE_DIR){};
	
	inline sock_t & socket() { return socket_; }

	void start_processing();
	
private:
	//methods
	void write_completion_handler(const errc & err, size_t bytes_transferred);
	void read_completion_handler(const	errc & err, size_t bytes_transferred);
	void load_file(const std::string& filename);

private:
	//fields
	sock_t socket_;
	//strnd strand_;
	std::string response_string;
	response resp;

	boost::array<char,8192> buffer_;
};