#pragma once
#include <filesystem>
#include "../../core/non_copyable.hpp"
#include "../../core/typedefs.hpp"

namespace fs = std::filesystem;

//This is a base class for project settings
class settings_base : private non_copyable{

public:
	settings_base() {
		BASE_DIR_ = fs::current_path();
	}

	virtual ~settings_base() {}
protected:
	std::string BASE_DIR_ = "";
	std::string TEMPLATE_DIR_ = "";
	std::string REQ_FILE_ = "";
	std::string STATIC_DIR_ = "";

private:

	/*
		@Replaces all occurrences of "from" to "to" in given string
	*/
	std::string _replace_all(std::string str, const std::string& from, const std::string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
		return str;
	}

	/*
		@Returns absolute path to dirname of current file.
		Note that file path must be absolute for proper functioning.
		It is also compulsory to alter path style from \\ to /, since __FILE__ returns 
		path in former format.
	*/
	

	inline std::string _dirname(const std::string& file_path)
	{
		/*
		Check whether a path string has a trailing slash and,based on previous check,
		assign a corresponding value to starting_offset
		*/
		ui16 i{ 0 };
		ui16 starting_offset = (file_path[file_path.length() - 1] == '/') ? file_path.length() - 2
																		: file_path.length() - 1;
		auto found = file_path.find_last_of("/");


		return file_path.substr(0, found);
	}
};