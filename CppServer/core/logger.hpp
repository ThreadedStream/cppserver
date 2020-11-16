#pragma once
#include <iostream>
#include "typedefs.hpp"

enum class SEVERITY {
	DEBUG,
	INFO,
	ERR
};


class Logger final
{
public:
	Logger() = default;
	template<class str_class = const char*>
	static void log(SEVERITY type, str_class message){
		auto severity = parseSeverity(type);
		std::cout << "[" << severity << "]" << ": " << message;
	}

	template<>
	static void log(SEVERITY type, std::string message) {
		auto severity = parseSeverity(type);
		std::cout << "[" << severity << "]" << ": " << message.c_str();
	}

	template<>
	static void log(SEVERITY type, streambuf* buf) {
		auto severity = parseSeverity(type);
		std::cout << "[" << severity << "]" << ": " << &buf;
	}

private:
	static const char * parseSeverity(SEVERITY type)
	{
		switch (type)
		{
		case SEVERITY::DEBUG:
			return "DEBUG";
			break;
		
		case SEVERITY::INFO:
			return "INFO";
			break;
		
		case SEVERITY::ERR:
			return "ERROR";
			break;
		default:
			return "UNDEFINED";
			break;
		}
	}

};