// module to refer to sequences of bytecode
#ifndef clox_chunk_h
#define clox_chunk_h

#include "../common.h"
#include <stdint.h>

// enum to define opcodes
typedef enum {
    OP_RETURN,
} Opcode;

// struct to define a chunk
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);

#endif
