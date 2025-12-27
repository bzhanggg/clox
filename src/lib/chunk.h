#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include "value.h"

#include <cstdint>
#include <vector>

namespace clox {

enum OpCode { OP_CONSTANT, OP_RETURN };

struct Chunk {
  /**
   * @brief Adds raw bytes to the bytecode chunk
   */
  void writeChunk(const uint8_t byte);

  /**
   * @brief Adds a constant to the bytecode chunk
   *
   * @param value the constant to be added
   * @return int the index at which the constant was added
   */
  int addConstant(const Value value);

  std::vector<uint8_t> code;
  std::vector<Value> constants;
};

} // namespace clox

#endif // CLOX_CHUNK_H_