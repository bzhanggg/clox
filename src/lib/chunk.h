#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include <cstdint>
#include <vector>

namespace clox {

enum OpCode { OP_RETURN };

using Chunk = std::vector<uint8_t>;

namespace lib {

class Disassembler {
public:
  static void disassembleChunk(const Chunk &chunk, const std::string &name);
  static int disassembleInstruction(const Chunk &chunk, int offset);

private:
  static int simpleInstruction(const std::string &instrName, int offset);
};

} // namespace lib
} // namespace clox

#endif // CLOX_CHUNK_H_