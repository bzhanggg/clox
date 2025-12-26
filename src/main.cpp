#include "chunk.h"

using namespace clox;

int main(int argc, const char* argv[]) {
    Chunk chunk;
    chunk.emplace_back(OP_RETURN);

    lib::Disassembler::disassembleChunk(chunk, "test chunk");
    
    return 0;
}
