#include "lzss.h"
#include <cstring>

namespace th10 {

static const size_t DICT_SIZE  = 0x2000;
static const size_t DICT_MASK  = 0x1FFF;
static const size_t MIN_MATCH  = 3;
static const size_t MAX_MATCH  = 18;

struct BitReader {
    const uint8_t* src;
    const uint8_t* src_end;
    uint8_t mask;
    uint8_t current;

    BitReader(const uint8_t* data, size_t size)
        : src(data), src_end(data + size), mask(0), current(0) {}

    int next_bit() {
        if (mask == 0) {
            if (src >= src_end) return -1;
            current = *src++;
            mask = 0x80;
        }
        int bit = (current & mask) ? 1 : 0;
        mask >>= 1;
        return bit;
    }

    int read_bits(int n) {
        int value = 0;
        for (int i = 0; i < n; i++) {
            int bit = next_bit();
            if (bit < 0) return -1;
            value = (value << 1) | bit;
        }
        return value;
    }
};

std::vector<uint8_t> lzss_decompress(const uint8_t* data, size_t size, size_t output_size) {
    std::vector<uint8_t> output;
    if (output_size == 0 || size == 0) return output;
    output.reserve(output_size);

    uint8_t dict[DICT_SIZE];
    memset(dict, 0, DICT_SIZE);
    size_t dict_pos = 1;

    BitReader reader(data, size);

    while (output.size() < output_size) {
        int bit = reader.next_bit();
        if (bit < 0) break;

        if (bit == 1) {
            int byte_val = reader.read_bits(8);
            if (byte_val < 0) break;
            output.push_back((uint8_t)byte_val);
            dict[dict_pos] = (uint8_t)byte_val;
            dict_pos = (dict_pos + 1) & DICT_MASK;
        } else {
            int offset = reader.read_bits(13);
            if (offset < 0) break;
            if (offset == 0) break;

            int length_raw = reader.read_bits(4);
            if (length_raw < 0) break;
            size_t match_len = (size_t)length_raw + MIN_MATCH;

            for (size_t i = 0; i < match_len && output.size() < output_size; i++) {
                uint8_t c = dict[(offset + i) & DICT_MASK];
                output.push_back(c);
                dict[dict_pos] = c;
                dict_pos = (dict_pos + 1) & DICT_MASK;
            }
        }
    }

    return output;
}

} // namespace th10
