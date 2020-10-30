#pragma once

#include "typedefs.hpp"
#include "non_constructible.h"
#include "non_copyable.hpp"
#include "logger.hpp"
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>

//Singleton class, denoting Database Connection
class dbconn : private non_copyable, private non_constructible {
public:
	FORCE_INLINE static dbconn* getInstance() { return instance; }

	bool init_conn();

private:
	static dbconn* instance;
};
