#pragma once

#include "../core/logger.hpp"

struct sync_client {
	sock_ptr_t socket_;
	std::string reqbuf;

	void initiate(err_code& err) {
		if (socket_->is_open()) {
			Logger::log(SEVERITY::DEBUG, "Attempting to write some data\n");
			sync_write(err);
			if (err.cause == "") {
				sync_read(err);
			}
			else {
				return;
			}
		}
		else {
			err.cause = "Socket is closed\n";
			return;
		}
	}

	void operator()(err_code& err) {
		initiate(err);
	}

private:
	void sync_write(err_code& err) {
		errc err_write;
		socket_->write_some(buffer(reqbuf, reqbuf.length()), err_write);
		if (err_write) {
			err.cause = err_write.message();
			return;
		}
	}
	void sync_read(err_code& err) {
		errc err_read;
		
		streambuf respbuf;
		try {
			read_until(*socket_.get(), respbuf, "\r\n\r\n");
		}
		catch (const boost::system::system_error& err){
			std::cout << err.what();
		}
		std::istream response_stream(&respbuf);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		Logger::log(SEVERITY::DEBUG, "Response returned " + (status_code));
		std::cout << &respbuf;
	}
};