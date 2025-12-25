#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include <vector>

namespace clox {
namespace lib {

enum class OpCode {
    OP_RETURN
};

using Chunk = std::vector<uint8_t>;

}
}

#endif // CLOX_CHUNK_H_