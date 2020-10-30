#include "dbconn.hpp"

bool dbconn::init_conn()
{
	
	sql::mysql::MySQL_Driver *driver;
	sql::Connection* conn;

	driver = sql::mysql::get_mysql_driver_instance();
	conn = driver->connect("95.214.63.31:3306", "root", "VL6d&zHv");
	if (conn)
		return true;
	else
		return false;
}