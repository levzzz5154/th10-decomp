#include "th10/archive/lzss.hpp"

extern "C" void* __cdecl _malloc(uint32_t size);

namespace {

const uint32_t kDictionarySize = 0x2000;
const uint32_t kDictionaryMask = kDictionarySize - 1;
uint8_t g_dictionary[kDictionarySize];

class BitReader {
public:
    BitReader(const uint8_t* input, int32_t size)
        : input_(input), size_(size), offset_(0), current_(0), mask_(0x80) {}

    bool ReadBit() {
        if (mask_ == 0x80) {
            current_ = offset_ < size_ ? input_[offset_++] : 0;
        }
        bool set = (current_ & mask_) != 0;
        mask_ >>= 1;
        if (mask_ == 0) {
            mask_ = 0x80;
        }
        return set;
    }

    uint32_t ReadBits(uint32_t value_mask) {
        uint32_t value = 0;
        while (value_mask != 0) {
            if (ReadBit()) {
                value |= value_mask;
            }
            value_mask >>= 1;
        }
        return value;
    }

private:
    const uint8_t* input_;
    int32_t size_;
    int32_t offset_;
    uint8_t current_;
    uint8_t mask_;
};

} // namespace

uint8_t* __stdcall Dat_LzssDecompress(
        const uint8_t* input,
        int32_t input_size,
        uint8_t* output,
        uint32_t output_size) {
    uint8_t* result = output;
    if (!result) {
        result = (uint8_t*)_malloc(output_size);
        if (!result) {
            return 0;
        }
    }

    BitReader bits(input, input_size);
    uint8_t* destination = result;
    uint32_t dictionary_position = 1;

    for (;;) {
        if (bits.ReadBit()) {
            uint8_t literal = (uint8_t)bits.ReadBits(0x80);
            *destination++ = literal;
            g_dictionary[dictionary_position] = literal;
            dictionary_position = (dictionary_position + 1) & kDictionaryMask;
            continue;
        }

        uint32_t dictionary_offset = bits.ReadBits(0x1000);
        if (dictionary_offset == 0) {
            break;
        }

        uint32_t length_code = bits.ReadBits(8);
        uint32_t length = length_code + 3;
        for (uint32_t index = 0; index < length; ++index) {
            uint8_t value =
                g_dictionary[(dictionary_offset + index) & kDictionaryMask];
            *destination++ = value;
            g_dictionary[dictionary_position] = value;
            dictionary_position = (dictionary_position + 1) & kDictionaryMask;
        }
    }

    return result;
}
