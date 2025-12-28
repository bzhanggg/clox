#include "vm.h"
#include "chunk.h"

#define DEBUG_TRACE_EXECUTION
#ifdef DEBUG_TRACE_EXECUTION
#include "debug.h"
#include <algorithm>
#endif

#include <cstdint>

namespace clox {

VM::VM(const Chunk &chunk) : chunk{chunk}, ip{chunk.code.data()}, stack{} {}

const InterpretResult VM::interpret() { return run(); }

const InterpretResult VM::run() {
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    std::printf("          ");
    std::for_each(stack.cbegin(), stack.cend(), [](Value s) {
      std::print("[ ");
      printValue(s);
      std::print(" ]");
    });
    std::print("\n");
    debug::Disassembler::disassembleInstruction(
        chunk, static_cast<int>(ip - chunk.code.data()));
#endif // DEBUG_TRACE_EXECUTION
    uint8_t instruction;
    switch (instruction = read_byte()) {
    case OP_CONSTANT: {
      Value constant = read_constant();
      stack.emplace_back(constant);
      break;
    }
    case OP_RETURN: {
      printValue(stack.back());
      stack.pop_back();
      std::print("\n");
      return INTERPRET_OK;
    }
    }
  }
}

inline const uint8_t VM::read_byte() { return *ip++; }

inline const double VM::read_constant() { return chunk.constants[read_byte()]; }

} // namespace clox