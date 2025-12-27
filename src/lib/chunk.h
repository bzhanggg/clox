#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include "value.h"

#include <cstdint>
#include <vector>

namespace clox {

enum OpCode { OP_CONSTANT, OP_RETURN };

struct LineInfo {
  int offset;
  int lineNum;
};

struct Chunk {

  Chunk() = default;
  ~Chunk() = default;

  /**
   * @brief Adds raw bytes to the bytecode chunk
   */
  void writeChunk(const uint8_t byte, const int lineNumber);

  /**
   * @brief finds the line number of a bytecode op given its offset in the code
   */
  int getLine(const int offset) const;

  /**
   * @brief Adds a constant to the bytecode chunk
   *
   * @param value the constant to be added
   * @return int the index at which the constant was added
   */
  int addConstant(const Value value);

  std::vector<uint8_t> code;
  std::vector<LineInfo> lines;
  std::vector<Value> constants;
};

} // namespace clox

#endif // CLOX_CHUNK_H_