#ifndef CLOX_VM_H_
#define CLOX_VM_H_

#include "chunk.h"

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

  const InterpretResult interpret();

private:
  const InterpretResult run();

  inline const uint8_t READ_BYTE();
  inline const double READ_CONSTANT();
  inline const double READ_CONSTANT_LONG();

  const Chunk &chunk;
  const uint8_t *ip; // points to the next instruction to be executed
  std::vector<Value> stack;
};

} // namespace clox

#endif // CLOX_VM_H_