#include "util_xor.h"

namespace th10 {

void util_xor(uint8_t* data, size_t size, uint8_t key, uint8_t step1, uint8_t step2) {
    while (size-- > 0) {
        *data++ ^= key;
        key += step1;
        step1 += step2;
    }
}

} // namespace th10
