#ifndef CLOX_COMPILER_H_
#define CLOX_COMPILER_H_

#include <string>

namespace clox {

class Compiler {
public:
  void compile(const std::string& source);
private:
};

}


#endif // CLOX_COMPILER_H_