#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include "value.h"

#include <cstdint>
#include <vector>

namespace clox {

enum OpCode { OP_CONSTANT, OP_CONSTANT_LONG, OP_RETURN };

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
   * @brief writes an OP_CONSTANT or OP_CONSTANT_LONG to the constants vector
   *
   * @param value the constant to be written
   * @param line the line at which the constant is written
   */
  void writeConstant(const Value value, int line);

  std::vector<uint8_t> code;
  std::vector<LineInfo> lines;
  std::vector<Value> constants;

private:

  /**
   * @brief Adds a constant to the bytecode chunk
   *
   * @param value the constant to be added
   * @return int the index at which the constant was added
   */
  int addConstant(const Value value);
};

} // namespace clox

#endif // CLOX_CHUNK_H_