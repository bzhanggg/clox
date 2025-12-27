#ifndef CLOX_DEBUG_H_
#define CLOX_DEBUG_H_

#include "chunk.h"

#include <string>

namespace clox {
namespace debug {

class Disassembler {
public:
  static void disassembleChunk(const Chunk &chunk, const std::string &name);
  static int disassembleInstruction(const Chunk &chunk, const int offset);

private:
  static int simpleInstruction(const std::string &instrName, const int offset);
  static int constantInstruction(const std::string &instrName,
                                 const Chunk &chunk, const int offset);
  static int constantLongInstruction(const std::string &instrName,
                                     const Chunk &chunk, const int offset);
};

} // namespace debug
} // namespace clox

#endif // CLOX_DEBUG_H_