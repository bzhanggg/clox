#include "chunk.h"
#include "vm.h"

using namespace clox;

int main(int argc, const char *argv[]) {
  Chunk chunk;

  chunk.writeConstant(1.2, 123);
  chunk.writeConstant(3.4, 123);

  chunk.writeChunk(OpCode::OP_ADD, 123); // 1.2 + 3.4

  chunk.writeConstant(5.6, 123);
  chunk.writeChunk(OpCode::OP_DIVIDE, 123); // (1.2 + 3.4) / 5.6

  chunk.writeChunk(OpCode::OP_NEGATE, 123); // - ((1.2 + 3.4) / 5.6)
  chunk.writeChunk(OpCode::OP_RETURN, 123);

  VM vm(chunk);
  vm.interpret();

  return 0;
}
