#include "vm.h"
#include "chunk.h"

#define DEBUG_TRACE_EXECUTION
#ifdef DEBUG_TRACE_EXECUTION
#include "debug.h"
#include <algorithm>
#endif

#include <cstdint>
#include <fstream>
#include <iostream>
#include <print>

namespace clox {

VM::VM(const Chunk &chunk) : chunk{chunk}, ip{chunk.code.data()}, stack{} {}

void VM::repl() {
  std::string line;
  for (;;) {
    std::cout << "> " << std::flush;
    if (!std::getline(std::cin, line)) {
      std::cout << '\n';
      break;
    }
    if (line.empty())
      continue;
    interpret(line);
  }
}

void VM::runFile(const std::string &fpath) {
  std::string line;
  std::ifstream file{fpath};

  if (file.is_open()) {
    while (std::getline(file, line)) {
      interpret(line);
    }
  } else {
    std::cerr << "Error: Unable to open file " << fpath << std::endl;
  }
}

const InterpretResult VM::interpret(const std::string &source) {
  compiler.compile(source);
  return INTERPRET_OK;
}

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
    switch (instruction = READ_BYTE()) {
    case OpCode::OP_CONSTANT: {
      const Value constant = READ_CONSTANT();
      stack.emplace_back(constant);
      break;
    }
    case OpCode::OP_CONSTANT_LONG: {
      const Value longConstant = READ_CONSTANT_LONG();
      stack.emplace_back(longConstant);
      break;
    }
    case OpCode::OP_NEGATE: {
      stack.back() = -stack.back();
      break;
    }
    case OpCode::OP_ADD: {
      BINARY_OP_ADD();
      break;
    }
    case OpCode::OP_SUBTRACT: {
      BINARY_OP_SUB();
      break;
    }
    case OpCode::OP_MULTIPLY: {
      BINARY_OP_MUL();
      break;
    }
    case OpCode::OP_DIVIDE: {
      BINARY_OP_DIV();
      break;
    }
    case OpCode::OP_RETURN: {
      printValue(stack.back());
      stack.pop_back();
      std::print("\n");
      return INTERPRET_OK;
    }
    }
  }
}

inline const uint8_t VM::READ_BYTE() { return *ip++; }

inline const double VM::READ_CONSTANT() { return chunk.constants[READ_BYTE()]; }

inline const double VM::READ_CONSTANT_LONG() {
  uint8_t byte1 = READ_BYTE();
  uint8_t byte2 = READ_BYTE();
  uint8_t byte3 = READ_BYTE();
  size_t index = (byte1 << 16) | (byte2 << 8) | byte3;
  return chunk.constants[index];
}

inline void VM::BINARY_OP_ADD() {
  binaryOp([](double a, double b) { return a + b; });
}

inline void VM::BINARY_OP_SUB() {
  binaryOp([](double a, double b) { return a - b; });
}

inline void VM::BINARY_OP_MUL() {
  binaryOp([](double a, double b) { return a * b; });
}

inline void VM::BINARY_OP_DIV() {
  binaryOp([](double a, double b) { return a / b; });
}

} // namespace clox