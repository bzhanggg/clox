#include "scanner.h"

#include <print>
#include <string_view>

namespace clox {

ErrorToken::ErrorToken(const std::string &message, const int line)
    : Token{TokenType::e_ERROR, message.data(), message.length(), line} {}

Scanner::Scanner(const std::string &source)
    : source{source}, start{source.data()}, current{source.data()}, line{1} {}

void Scanner::scan() {
  int line = -1;
  while (true) {
    Token token = scanToken();
    if (token.line != line) {
      std::print("{:4d}", token.line);
      line = token.line;
    } else {
      std::print("   | ");
    }
    std::print("{:2d} '{}'\n",
               static_cast<std::underlying_type_t<TokenType>>(token.type),
               std::string_view{token.start, token.length});

    if (token.type == TokenType::e_EOF)
      break;
  }
}

Token Scanner::scanToken() {
  start = current;

  if (isAtEnd()) {
    return Token{TokenType::e_EOF, start, static_cast<size_t>(current - start),
                 line};
  }

  return ErrorToken("Unexpected character.", line);
}

bool Scanner::isAtEnd() { return *current == '\0'; }

} // namespace clox