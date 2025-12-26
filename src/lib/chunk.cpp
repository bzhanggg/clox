#include <cstdint>
#include <print>

#include "chunk.h"

namespace clox {
namespace lib {

void Disassembler::disassembleChunk(const Chunk &chunk,
                                    const std::string &name) {
  std::print("== {} ==\n", name);

  for (int offset = 0; offset < chunk.size();) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int Disassembler::disassembleInstruction(const Chunk &chunk, int offset) {
  std::print("{:04d} ", offset);

  uint8_t instruction = chunk[offset];
  switch (instruction) {
  case OpCode::OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);
  default:
    std::print("Unknown opcode %d\n", instruction);
    return offset + 1;
  }
}

int Disassembler::simpleInstruction(const std::string &instrName, int offset) {
  std::print("{}\n", instrName);
  return offset + 1;
}

} // namespace lib
} // namespace clox