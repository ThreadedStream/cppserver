#pragma once
#include "../../core/non_copyable.hpp"
#include <string>

//This is a base class for project settings
class settings_base : private non_copyable{

public:
	settings_base(const std::string& basedir,
				  const std::string& templatedir):
				 BASE_DIR_(basedir), TEMPLATE_DIR_(basedir + "/" + templatedir){}


	virtual ~settings_base() {}
protected:
	std::string BASE_DIR_ = "";
	std::string TEMPLATE_DIR_ = "";
	std::string REQ_FILE_ = "";
};