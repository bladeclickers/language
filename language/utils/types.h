#pragma once

#include <functional>
#include <vector>
#include <string>

enum types {
	function,
	type,
	identifier,
	op,
	number,
	advance,
	null
};

enum chardefs {
	split = ' ',
	separate = ',',
	adv = ';',
};

inline std::vector<std::string> builtins = {
	"print"
};

inline std::vector<std::string> builtin_types = {
	"var"
};

struct type_dec {
	std::string name;
	types type;
};

struct var_key {
	std::string name;
	std::string value;
};

struct func {
	std::string name;
	std::vector<std::string> args;
};

typedef std::vector<std::vector<type_dec>> lexer_out;