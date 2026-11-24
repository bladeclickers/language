#include "lexer.h"

namespace lexer {
    lexer_out lexer(std::string input) {
        lexer_out out{};

        std::vector<std::string> lines{};

        std::string temp_instruction{};

        for (int i = 0; i < input.size(); i++) {
            if (input.at(i) != chardefs::end) {
                temp_instruction += input.at(i);
            } else {
                lines.emplace_back(temp_instruction);
                temp_instruction.clear();
            }
        }

        if (!temp_instruction.empty()) {
            lines.emplace_back(temp_instruction);
        }

        for (std::string line : lines) {
            std::vector<std::string> words{};

            std::string temp_word{};

            for (int i = 0; i < line.size(); i++) {
                if (!std::isspace(line.at(i))) {
                    temp_word += line.at(i);
                } else {
                    if (!temp_word.empty()) {
                        words.emplace_back(temp_word);
                        temp_word.clear();
                    }
                }
            }

            if (!temp_word.empty()) {
                words.emplace_back(temp_word);
            }

            for (std::string word : words) {
                if (word.find("balls") != std::string::npos) {
                    std::cout << "balls";
                }
            }
        }

        return out;
    }
}