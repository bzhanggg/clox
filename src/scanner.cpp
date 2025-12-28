#include "scanner.h"

#include <iostream>

namespace clox {

Scanner::Scanner(const std::string& source)
: source{source}
, line{1}
{
}

void Scanner::scan() {
  int line = -1;
  for (;;) {
    Token token = scanToken();
    if (token.line != line) {
      std::cout << token.line;
      line = token.line;
    } else {
      std::cout << "    | ";
    }
    std::print("{:2d} '{:.*s}'\n", token.type, token.length, token.start);

    if (token.type == TokenType::e_EOF) break;
  }
}

}