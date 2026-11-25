#include <filesystem>
#include <fstream>
#include <sstream>

#include "utils/interpreter.h"

#define view_lexer_out false
#define view_variables false

std::string load_file(std::string path) {
    try {
        std::ifstream file(path);
        if (!file) {
            return "";
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    catch (...) {
        return "";
    }
}

int main(int argc, char** argv)
{
    std::string path = "";

    if (argc == 2) {
        path = argv[2];
    }
    else if (argc == 1) {
        std::cout << "input file path: ";
        std::cin >> path;
        system("cls");
    }
    else {
        std::cout << "incorrect arguments.";
        return -1;
    }

    lexer_out lexed = lexer::lexer(load_file(path));

#if view_lexer_out
    for (std::vector<type_dec> type_d : lexed) {
        for (type_dec type : type_d) {
            std::cout << type.name << ": " << type.type << ", ";
        }
        std::cout << std::endl;
    }
#endif

    interpreter::interpret(lexed);

#if view_variables
    for (var_key variable : interpreter::variables) {
        std::cout << variable.name << ": " << variable.value << std::endl;
    }
#endif

    while (true) {}
}