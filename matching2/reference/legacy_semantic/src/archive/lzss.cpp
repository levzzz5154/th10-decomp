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

class BitWriter {
public:
    BitWriter(uint8_t* output)
        : output_(output), offset_(0), mask_(0x80) {}

    void WriteBit(bool set) {
        if (mask_ == 0x80) {
            output_[offset_] = 0;
        }
        if (set) {
            output_[offset_] |= mask_;
        }
        mask_ >>= 1;
        if (mask_ == 0) {
            mask_ = 0x80;
            ++offset_;
        }
    }

    void WriteBits(uint32_t value, uint32_t value_mask) {
        while (value_mask != 0) {
            WriteBit((value & value_mask) != 0);
            value_mask >>= 1;
        }
    }

    int32_t Size() const {
        return (int32_t)(offset_ + (mask_ == 0x80 ? 0 : 1));
    }

private:
    uint8_t* output_;
    uint32_t offset_;
    uint8_t mask_;
};

} // namespace

uint8_t* __stdcall Dat_LzssCompress(
        const uint8_t* input,
        int32_t input_size,
        int32_t* output_size) {
    if (!output_size || input_size < 0) {
        return 0;
    }
    *output_size = 0;

    uint32_t capacity = (uint32_t)input_size * 2 + 2;
    uint8_t* output = (uint8_t*)_malloc(capacity);
    if (!output) {
        return 0;
    }

    BitWriter bits(output);
    int32_t position = 0;
    while (position < input_size) {
        int32_t best_position = -1;
        int32_t best_length = 0;
        int32_t window_start = position > (int32_t)kDictionarySize
            ? position - (int32_t)kDictionarySize : 0;
        int32_t maximum_length = input_size - position;
        if (maximum_length > 18) maximum_length = 18;

        for (int32_t candidate = position - 1;
                candidate >= window_start; --candidate) {
            uint32_t dictionary_offset =
                ((uint32_t)candidate + 1) & kDictionaryMask;
            if (dictionary_offset == 0 ||
                    input[candidate] != input[position]) {
                continue;
            }
            int32_t length = 1;
            while (length < maximum_length &&
                    input[candidate + length] == input[position + length]) {
                ++length;
            }
            if (length > best_length) {
                best_length = length;
                best_position = candidate;
                if (best_length == maximum_length) break;
            }
        }

        if (best_length >= 3) {
            bits.WriteBit(false);
            bits.WriteBits(
                ((uint32_t)best_position + 1) & kDictionaryMask,
                0x1000);
            bits.WriteBits((uint32_t)(best_length - 3), 8);
            position += best_length;
        } else {
            bits.WriteBit(true);
            bits.WriteBits(input[position], 0x80);
            ++position;
        }
    }

    bits.WriteBit(false);
    bits.WriteBits(0, 0x1000);
    *output_size = bits.Size();
    return output;
}

// 0x00435DC0 - Decode TH10's bit-packed 0x2000-byte sliding-window stream.
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
