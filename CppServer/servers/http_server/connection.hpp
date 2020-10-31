#pragma once
#include "../../core/logger.hpp"
#include "../../core/non_copyable.hpp"
#include "../../core/dbconn.hpp"
#include "response.hpp"

//NOTE: Temporary declarations
#define FILENAME_DEMO "F:/demo.cpp"
#define FILENAME "index.html"
#define TEMPLATE_DIR "F:/cppserver/CppServer/templates"
#define DBLOGFILE "F:/cppserver/CppServer/dblog.txt"

class connection : 
	public boost::enable_shared_from_this<connection>,
	private non_copyable
{
public:
	explicit connection(asio_ctx& context) :
		//strand_(make_strand(context)),
		//connInstance(dbconn::getInstance()),
		socket_(context),
		//Note that trailing slash is required for proper functioning
		resp(TEMPLATE_DIR),
		dblog{ DBLOGFILE, std::ofstream::out | std::ofstream::trunc} {};
	
	inline sock_t & socket() { return socket_; }

	void start_processing();
	
private:
	//methods
	void write_completion_handler(const errc & err, size_t bytes_transferred);
	void read_completion_handler(const	errc & err, size_t bytes_transferred);
	void load_file(const std::string& filename);
	void initDBConnection(err_code& err);
	void write_headers_to_file(const std::string& str,err_code& err);

private:
	//fields
	sock_t socket_;
	//strnd strand_;
	std::string response_string;
	response resp;
	//boost::shared_ptr<dbconn> connInstance;

	boost::array<char,8192> buffer_;
	std::ofstream dblog;
};