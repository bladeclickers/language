#include "utils/lexer.h"

std::string script = "hi this is a test\ni have balls\nhi";

int main() {
    lexer::lexer(script);
    return 0;
}