#include "debug.h"

#include <cstdint>
#include <print>

namespace clox {
namespace debug {

void Disassembler::disassembleChunk(const Chunk &chunk,
                                    const std::string &name) {
  std::print("== {} ==\n", name);

  for (int offset = 0; offset < chunk.code.size();) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int Disassembler::disassembleInstruction(const Chunk &chunk, const int offset) {
  std::print("{:04d} ", offset);

  uint8_t instruction = chunk.code[offset];
  switch (instruction) {
  case OpCode::OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  case OpCode::OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);
  default:
    std::print("Unknown opcode %d\n", instruction);
    return offset + 1;
  }
}

int Disassembler::simpleInstruction(const std::string &instrName,
                                    const int offset) {
  std::print("{}\n", instrName);
  return offset + 1;
}

int Disassembler::constantInstruction(const std::string &instrName,
                                      const Chunk &chunk, const int offset) {
  uint8_t constant = chunk.code[offset + 1];
  std::print("{:<16} {:4} '", instrName, constant);
  printValue(chunk.constants[constant]);
  std::print("'\n");
  return offset + 2;
}

} // namespace debug
} // namespace clox