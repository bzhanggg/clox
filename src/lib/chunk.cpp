#include "chunk.h"

namespace clox {

void Chunk::writeChunk(const uint8_t byte, const int lineNumber) {
  code.emplace_back(byte);
  if (lines.empty() || lines.back().lineNum != lineNumber) {
    lines.emplace_back(code.size() - 1, lineNumber);
  }
}

int Chunk::addConstant(const Value value) {
  constants.emplace_back(value);
  return constants.size() - 1;
}

int Chunk::getLine(const int offset) const {
  for (int i = lines.size() -1; i >= 0; --i) {
    if (lines[i].offset <= offset) return lines[i].lineNum;
  }
  return 1;
}

} // namespace clox