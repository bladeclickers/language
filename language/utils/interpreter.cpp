#include "interpreter.h"

namespace interpreter {
	var_key* get_variable(std::string name) {
		for (var_key& variable : variables) {
			if (variable.name == name) return &variable;
		}
		return nullptr;
	}

	float resolve_operand(std::string operand) {
		try {
			return std::stof(operand);
		}
		catch (...) {
			var_key* variable = get_variable(operand);
			if (variable) return std::stof(variable->value);
		}
	}

	float do_operand(std::string op, std::string arg1, std::string arg2) {
		float a = resolve_operand(arg1);
		float b = resolve_operand(arg2);

		if (op == "+") return a + b;
		if (op == "-") return a - b;
		if (op == "*") return a * b;
		if (op == "/") return a / b;

		return -1;
	}

	func parse_func(type_dec input) {
		size_t args_start = input.name.find("(");
		size_t args_end = input.name.find(")");

		std::string func = input.name.substr(0, args_start);
		std::string args = input.name.substr(args_start + 1, args_end - args_start - 1);

		std::string temp_arg{};
		std::vector<std::string> arg_list{};

		args.erase(args.begin(), std::find_if(args.begin(), args.end(), [](unsigned char c) { return !std::isspace(c); }));

		for (size_t r = 0; r < args.size(); r++) {
			if (args.at(r) == chardefs::separate) {
				arg_list.emplace_back(temp_arg);
				temp_arg = "";
			}
			else {
				temp_arg += args.at(r);
			}
		}

		if (!temp_arg.empty()) arg_list.emplace_back(temp_arg);

		return { func, arg_list };
	}

	void run_builtin(std::string name, std::vector<std::string> args) {
		if (name == "print") {
			for (std::string arg : args) {
				std::cout << arg;
			}
		}
	}

	std::string trim(std::string str) {
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isspace(c); }));
		str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), str.end());
		return str;
	}

	void interpret(lexer_out input) {
		for (std::vector<type_dec> type_v : input) {
			types line_type = types::null;
			for (type_dec type : type_v) {
				if (type.type == types::op) {
					line_type = types::op;
					break;
				}
				else if (type.type == types::function) {
					line_type = types::function;
					break;
				}
			}
			if (line_type == types::op) {
				if (type_v.size() < 4) continue;

				std::string variable_name = type_v[1].name;
				std::string result;

				if (type_v.size() == 4) {
					result = std::to_string(resolve_operand(type_v[3].name));
				}
				else if (type_v.size() == 6) {
					result = std::to_string(do_operand(type_v[4].name, type_v[3].name, type_v[5].name));
				}

				var_key* existing = get_variable(variable_name);
				if (existing) existing->value = result;
				else variables.emplace_back(var_key{ variable_name, result });
			}
			else {
				func parsed_func = parse_func(type_v[0]);

				std::vector<std::string> values{};

				for (std::string var_name : parsed_func.args) {
					var_key* var = get_variable(var_name);

					if (var == nullptr) {
						values.emplace_back(var_name);
					}
					else {
						values.emplace_back(var->value);
					}
				}

				run_builtin(trim(parsed_func.name), values);
			}
		}
	}
}