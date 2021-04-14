#pragma once
#include <vector>
#include <regex>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/classification.hpp> // For is_any_of()
#include <boost/range/iterator_range.hpp>
#include <functional>


namespace tokens {
	enum class Tokens{
		TAN, // tan(x)
		COS, // cos(x)
		SIN, // sin(x)
		COT, // cot(x)
		POWER, // ^
		LN, // ln(x)
		MUL, // *
		ADD, // +
		SUB, // -
		UNDEF, // undefined
	};
}

namespace funcs {
}


class math_unit
{
public:

	static std::vector<tokens::Tokens> tokenize(std::string &input, const char* sep) {
		boost::replace_all(input, "%20", sep);
		auto tokens = split(input, sep);
		std::vector<tokens::Tokens> toks;
		for (auto token : tokens) {
			toks.emplace_back(map_str_to_tok(token));
		}

		return toks;
	}

	static std::string toks_to_str(std::vector<tokens::Tokens> toks) {
		std::string tokenized;
		for (auto tok : toks) {
			tokenized += tok_to_str(tok);
			tokenized += ", ";
		}
		
		return tokenized;
	}


private:
	
	template<class R, class ... Args> 
	float evaluate(const std::function<R(Args...)>& fn, Args ... args){
		return fn(args...);
	}


	static std::string tok_to_str(const tokens::Tokens& tok) {
		switch (tok) {
		case tokens::Tokens::ADD:
			return "ADD";
		case tokens::Tokens::COS:
			return "COS";
		case tokens::Tokens::COT:
			return "COT";
		case tokens::Tokens::LN:
			return "LN";
		case tokens::Tokens::SIN:
			return "SIN";
		case tokens::Tokens::TAN:
			return "TAN";
		case tokens::Tokens::POWER:
			return "POWER";
		case tokens::Tokens::SUB:
			return "SUB";
		case tokens::Tokens::MUL:
			return "MUL";
		default:
			return "UNDEF";
		}
	}

	static std::vector<std::string> split(const std::string& str, const char* sep) {
		std::vector<std::string> tokens;	
		boost::split(tokens, str, boost::is_any_of(sep), boost::algorithm::token_compress_on);
		return tokens;
	}


	static tokens::Tokens map_str_to_tok(const std::string & token) {
		std::regex power_matcher("x\\^[0-9]*");
		if (token == "tan(x)") {
			return tokens::Tokens::TAN;
		}

		else if (token == "cos(x)") {
			return tokens::Tokens::COS;
		}

		else if (token == "sin(x)") {
			return tokens::Tokens::SIN;
		}

		else if (token == "cot(x)") {
			return tokens::Tokens::COT;
		}

		else if (std::regex_match(token, power_matcher)) {
			return tokens::Tokens::POWER;
		}

		else if (token == "ln(x)") {
			return tokens::Tokens::LN;
		}

		else if (token == "+") {
			return tokens::Tokens::ADD;
		}

		else if (token == "-") {
			return tokens::Tokens::SUB;
		}

		else if (token == "*") {
			return tokens::Tokens::MUL;
		}

		else {
			return tokens::Tokens::UNDEF;
		}
	}
};

