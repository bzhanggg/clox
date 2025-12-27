#include "chunk.h"

namespace clox {

void Chunk::writeChunk(const uint8_t byte) { code.emplace_back(byte); }

int Chunk::addConstant(const Value value) {
  constants.emplace_back(value);
  return constants.size() - 1;
}

} // namespace clox