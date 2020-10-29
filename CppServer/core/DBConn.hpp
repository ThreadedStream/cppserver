#pragma once

#include "typedefs.hpp"
#include "non_constructible.h"
#include "non_copyable.hpp"



//Singleton class, denoting Database Connection
class DBConn : private non_copyable, private non_constructible{

	FORCE_INLINE DBConn* getInstance() const { return instance; }

	void init_conn()
	{
														
	}

private:
	DBConn* instance;

};
