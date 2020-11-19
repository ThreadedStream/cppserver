#pragma once

#include "typedefs.hpp"

struct utils {

	/*
		@Splits the only string into two distinct ones, with the first 
		being header related and the other one being dedicated to a response data.
	*/
	static std::pair<std::string, std::string> split_response(const std::string& resp) {
		std::pair<std::string, std::string> pair;
		
		auto found_end_header = resp.find_last_of("\r\n\r\n");
		
		pair.first = resp.substr(0, found_end_header);
		pair.second = resp.substr(found_end_header);
		
		return pair;
	}


	
	static std::string prettify_json(std::string& json) {
		std::string pretty;
		
		pretty = json;

		replace_commas(pretty);

		return pretty;
	}

private:
	static void replace_commas(std::string& str) {
		for (int i = 0; i < str.length(); ++i) {
			if (str[i] == ',') {
				insert_str_at_pos(i, str, "<br>");
			}
		}
	}

	static void insert_str_at_pos(int pos, std::string& target, const std::string& in) {

	}
};