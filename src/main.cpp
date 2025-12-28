#include "chunk.h"
#include "vm.h"

using namespace clox;

int main(int argc, const char *argv[]) {
  Chunk chunk;

  chunk.writeConstant(1.23, 123);
  chunk.writeConstant(2.56, 123);

  chunk.writeChunk(OP_NEGATE, 123);
  chunk.writeChunk(OP_RETURN, 123);

  VM vm(chunk);
  vm.interpret();

  return 0;
}
