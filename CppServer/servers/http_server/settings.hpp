#pragma once
#include "settings_base.hpp"


class settings : public settings_base {

public:
	explicit settings(const std::string& basedir,
		const std::string& templatedir) : settings_base(basedir, templatedir) {}

	//getters' residency
	inline std::string base_dir() const { return BASE_DIR_; }
	inline std::string template_dir() const { return TEMPLATE_DIR_; }
	inline std::string req_file() const { return REQ_FILE_; }

	//setters' residency
	/*
		@Sets a full path to dblog.txt file
	*/
	inline void set_req_file(const std::string& req_file) { REQ_FILE_ = BASE_DIR_ + "/" + req_file; }

};