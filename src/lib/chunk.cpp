#include "chunk.h"

namespace clox {

void Chunk::writeChunk(const uint8_t byte, const int lineNumber) {
  code.emplace_back(byte);
  if (lines.empty() || lines.back().lineNum != lineNumber) {
    lines.emplace_back(code.size() - 1, lineNumber);
  }
}

int Chunk::getLine(const int offset) const {
  for (int i = lines.size() - 1; i >= 0; --i) {
    if (lines[i].offset <= offset)
      return lines[i].lineNum;
  }
  return 1;
}

int Chunk::addConstant(const Value value) {
  constants.emplace_back(value);
  return constants.size() - 1;
}

void Chunk::writeConstant(const Value value, const int line) {
  const int index = addConstant(value);

  if (index < 256) {
    writeChunk(OP_CONSTANT, line);
    writeChunk(index, line);
    return;
  }
  writeChunk(OP_CONSTANT_LONG, line);
  writeChunk((index >> 16) & 0xFF, line);
  writeChunk((index >> 8) & 0xFF, line);
  writeChunk((index) & 0xFF, line);
}

} // namespace clox