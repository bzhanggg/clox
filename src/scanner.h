#ifndef CLOX_SCANNER_H_
#define CLOX_SCANNER_H_

#include <string>

namespace clox {

enum class TokenType {
  // Single-character tokens
  e_LEFT_PAREN,
  e_RIGHT_PAREN,
  e_LEFT_BRACE,
  e_RIGHT_BRACE,
  e_COMMA,
  e_DOT,
  e_MINUS,
  e_PLUS,
  e_SEMICOLON,
  e_SLASH,
  e_STAR,
  // One or two character tokens
  e_BANG,
  e_BANG_EQUAL,
  e_EQUAL,
  e_EQUAL_EQUAL,
  e_GREATER,
  e_GREATER_EQUAL,
  e_LESS,
  e_LESS_EQUAL,
  // Literals
  e_IDENTIFIER,
  e_STRING,
  e_NUMBER,
  // Keywords
  e_AND,
  e_CLASS,
  e_ELSE,
  e_FALSE,
  e_FOR,
  e_FUN,
  e_IF,
  e_NIL,
  e_OR,
  e_PRINT,
  e_RETURN,
  e_SUPER,
  e_THIS,
  e_TRUE,
  e_VAR,
  e_WHILE,

  e_ERROR,
  e_EOF
};

struct Token {
  TokenType type;
  const char *start;
  size_t length;
  int line;
};

struct ErrorToken : Token {
  ErrorToken(const std::string &message, const int line);
};

class Scanner {
public:
  Scanner(const std::string &source);

  void scan();
  const Token scanToken();

private:
  const bool isAtEnd() const;
  const Token makeToken(const TokenType type) const;
  const char advance();
  const bool match(char expected);
  void skipWhitespace();

private:
  const std::string &source;
  const char *start;   // beginning of the current lexeme being scanned
  const char *current; // the current character being looked at

  int line;
};

} // namespace clox

#endif // CLOX_SCANNER_H_
