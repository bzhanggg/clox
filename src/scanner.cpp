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

const Token Scanner::scanToken() {
  skipWhitespace();
  start = current;

  if (isAtEnd()) {
    makeToken(TokenType::e_EOF);
  }

  char c = advance();

  switch(c) {
    case '(': return makeToken(TokenType::e_LEFT_PAREN);
    case ')': return makeToken(TokenType::e_RIGHT_PAREN);
    case '{': return makeToken(TokenType::e_LEFT_BRACE);
    case '}': return makeToken(TokenType::e_RIGHT_BRACE);
    case ';': return makeToken(TokenType::e_SEMICOLON);
    case ',': return makeToken(TokenType::e_COMMA);
    case '.': return makeToken(TokenType::e_DOT);
    case '-': return makeToken(TokenType::e_MINUS);
    case '+': return makeToken(TokenType::e_PLUS);
    case '/': return makeToken(TokenType::e_SLASH);
    case '*': return makeToken(TokenType::e_STAR);
    case '!':
      return makeToken(
          match('=') ? TokenType::e_BANG_EQUAL : TokenType::e_BANG);
    case '=':
      return makeToken(
          match('=') ? TokenType::e_EQUAL_EQUAL : TokenType::e_EQUAL);
    case '<':
      return makeToken(
          match('=') ? TokenType::e_LESS_EQUAL : TokenType::e_LESS);
    case '>':
      return makeToken(
          match('=') ? TokenType::e_GREATER_EQUAL : TokenType::e_GREATER);
    case '\n':

  }

  return ErrorToken("Unexpected character.", line);
}

const bool Scanner::isAtEnd() const { return *current == '\0'; }

const Token Scanner::makeToken(const TokenType type) const {
  return Token{type, start, static_cast<size_t>(current - start), line};
}

const char Scanner::advance() {
  current++;
  return current[-1];
}

const bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (*current != expected) return false;
  current++;
  return true;
}

// TODO: redo this starting from https://craftinginterpreters.com/scanning-on-demand.html#whitespace
void Scanner::skipWhitespace() {
  while (std::isspace(*current) || *current == '/') {
    if (*current == '/' && *(current++) == '/') {
      while (*current != '\n' && !isAtEnd()) current++;
    } else {
      return;
    }
    if (*current == '\n') {
      line++;
    }
    current++;
  }
}

} // namespace clox