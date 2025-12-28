#ifndef CLOX_VM_H_
#define CLOX_VM_H_

#include "chunk.h"
#include "compiler.h"

#include <vector>

namespace clox {

enum InterpretResult {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};

class VM {
public:
  VM() = delete;
  VM(const Chunk &chunk);

  void repl();
  void runFile(const std::string& fpath);
  const InterpretResult interpret(const std::string& source);

private:
  const InterpretResult run();

  const Chunk &chunk;
  const uint8_t *ip; // points to the next instruction to be executed
  std::vector<Value> stack;
  Compiler compiler;

private:
  inline const uint8_t READ_BYTE();
  inline const double READ_CONSTANT();
  inline const double READ_CONSTANT_LONG();
  inline void BINARY_OP_ADD();
  inline void BINARY_OP_SUB();
  inline void BINARY_OP_MUL();
  inline void BINARY_OP_DIV();

  template <typename Op> inline void binaryOp(Op operation) {
    const double b = stack.back();
    stack.pop_back();
    const double a = stack.back();
    stack.back() = operation(a, b);
  }
};

} // namespace clox

#endif // CLOX_VM_H_