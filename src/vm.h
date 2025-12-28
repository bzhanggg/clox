#ifndef CLOX_VM_H_
#define CLOX_VM_H_

#include "chunk.h"

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

  inline const uint8_t read_byte();
  inline const double read_constant();

  const Chunk &chunk;
  const uint8_t
      *ip; // instruction ptr points to the next instruction to be executed
};

} // namespace clox

#endif // CLOX_VM_H_