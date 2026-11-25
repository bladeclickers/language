#pragma once

#include "lexer.h"

#include <iostream>

namespace interpreter {
	inline std::vector<var_key> variables{};

	void interpret(lexer_out input);
}