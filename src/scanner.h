#ifndef CLOX_SCANNER_H_
#define CLOX_SCANNER_H_

#include <string>

namespace clox {

enum class TokenType {
  // Single-character tokens
  e_LEFT_PAREN, e_RIGHT_PAREN,
  e_LEFT_BRACE, e_RIGHT_BRACE,
  e_COMMA, e_DOT, e_MINUS, e_PLUS,
  e_SEMICOLON, e_SLASH, e_STAR,
  // One or two character tokens
  e_BANG, e_BANG_EQUAL,
  e_EQUAL, e_EQUAL_EQUAL,
  e_GREATER, e_GREATER_EQUAL,
  e_LESS, e_LESS_EQUAL,
  // Literals
  e_IDENTIFIER, e_STRING, e_NUMBER,
  // Keywords
  e_AND, e_CLASS, e_ELSE, e_FALSE,
  e_FOR, e_FUN, e_IF, e_NIL, e_OR,
  e_PRINT, e_RETURN, e_SUPER, e_THIS,
  e_TRUE, e_VAR, e_WHILE,

  e_ERROR, e_EOF
};

struct Token {
  TokenType type;
  const char *start;
  int length;
  int line;
};

class Scanner {
public:
  Scanner(const std::string& source);

  void scan();
  Token scanToken();

private:
  const std::string& source;
  int line;
};

}

#endif // CLOX_SCANNER_H_
