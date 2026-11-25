#include "lexer.h"

namespace lexer {
    lexer_out lexer(std::string input) {
        lexer_out final{};
        std::vector<std::string> lines{};
        std::string cur_line{};

        for (size_t i = 0; i < input.size(); i++) {
            if (input.at(i) == chardefs::adv) {
                lines.emplace_back(cur_line);
                cur_line = "";
            }
            else {
                cur_line += input.at(i);
            }
        }

        if (!cur_line.empty()) lines.emplace_back(cur_line);

        for (size_t i = 0; i < lines.size(); i++) {
            std::string temp_instr{};
            std::vector<std::string> instructions{};
            std::vector<type_dec> declarations{};

            lines[i].erase(lines[i].begin(), std::find_if(lines[i].begin(), lines[i].end(), [](unsigned char c) { return !std::isspace(c); }));

            for (size_t r = 0; r < lines[i].size(); r++) {
                if (lines[i].at(r) == chardefs::split) {
                    instructions.emplace_back(temp_instr);
                    temp_instr = "";
                }
                else {
                    temp_instr += lines[i].at(r);
                }
            }

            if (!temp_instr.empty()) instructions.emplace_back(temp_instr);

            for (size_t j = 0; j < instructions.size(); j++) {
                types type = types::null;

                bool is_number = !instructions[j].empty() && std::all_of(instructions[j].begin(), instructions[j].end(), [](unsigned char c) { return std::isdigit(c); });

                if (is_number) {
                    type = types::number;
                }
                else if (instructions[j] == "=" || instructions[j] == "+" || instructions[j] == "-" || instructions[j] == "/" || instructions[j] == "*") {
                    type = types::op;
                }
                else if (instructions[j] == "" || instructions[j] == " ") {
                    type = types::null;
                }
                else {
                    type = types::identifier;

                    for (std::string builtin : builtins) {
                        if (builtin == instructions[j]) type = types::function;
                    }
                    for (std::string builtin_type : builtin_types) {
                        if (builtin_type == instructions[j]) type = types::type;
                    }
                    if (instructions[j].find("(") != std::string::npos) {
                        type = types::function;
                    }
                }

                if (type != types::null) declarations.emplace_back(type_dec({ instructions[j], type }));
            }

            final.emplace_back(declarations);
        }

        return final;
    }
}