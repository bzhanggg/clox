#include "chunk.h"
#include "debug.h"

using namespace clox;

int main(int argc, const char* argv[]) {
    Chunk chunk;

    const int constant = chunk.addConstant(1.2);
    chunk.writeChunk(OP_CONSTANT);
    chunk.writeChunk(constant);

    chunk.writeChunk(OP_RETURN);

    debug::Disassembler::disassembleChunk(chunk, "test chunk");
        
    return 0;
}
