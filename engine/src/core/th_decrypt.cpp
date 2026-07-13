#include "th_decrypt.h"
#include <cstring>
#include <algorithm>
#include <vector>

namespace th10 {

const CryptParams th10_crypt_params[] = {
    { 'M', 0x1b, 0x37,   0x40, 0x2000 },
    { 'T', 0x51, 0xe9,   0x40, 0x3000 },
    { 'A', 0xc1, 0x51, 0x1400, 0x2000 },
    { 'J', 0x03, 0x19, 0x1400, 0x7800 },
    { 'E', 0xab, 0xcd,  0x200, 0x1000 },
    { 'W', 0x12, 0x34,  0x400, 0x2800 },
    { '-', 0x35, 0x97,   0x80, 0x2800 },
    { '*', 0x99, 0x37,  0x400, 0x1000 },
};

const size_t th10_crypt_params_count = sizeof(th10_crypt_params) / sizeof(th10_crypt_params[0]);

void th_decrypt(uint8_t* data, size_t size, uint8_t key, uint8_t step,
                uint32_t block, uint32_t limit) {
    if (size < block >> 2) size = 0;
    else size -= (size % block < block >> 2) * (size % block) + (size % 2);

    if (limit % block != 0)
        limit = limit + (block - (limit % block));

    size_t end_pos = size < limit ? size : limit;
    std::vector<uint8_t> temp(block);
    uint32_t increment = (block >> 1) + (block & 1);

    size_t pos = 0;
    while (pos < end_pos) {
        uint32_t chunk = (uint32_t)(end_pos - pos < block ? end_pos - pos : block);
        uint32_t inc = (chunk >> 1) + (chunk & 1);

        const uint8_t* in = data + pos;
        uint8_t* out = temp.data() + chunk - 1;

        while (out > temp.data()) {
            *out-- = *in ^ key;
            *out-- = *(in + inc) ^ (uint8_t)(key + step * inc);
            in++;
            key += step;
        }

        if (chunk & 1) {
            *out = *in ^ key;
            key += step;
        }
        key += step * inc;

        memcpy(data + pos, temp.data(), chunk);
        pos += chunk;
    }
}

} // namespace th10
