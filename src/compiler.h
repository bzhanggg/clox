#ifndef CLOX_COMPILER_H_
#define CLOX_COMPILER_H_

#include "scanner.h"

#include <string>

namespace clox {

class Compiler {
public:
  void compile(const std::string &source);

private:
  Scanner scanner;
};

} // namespace clox

#endif // CLOX_COMPILER_H_