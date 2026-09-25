// Readable models removed from matching2/msvc/src/archive/score_save.cpp: they compiled but did
// not reproduce the retail bytes, so that file keeps the exact assembly.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004359B0..0x00435DB4: LZSS compression with the retail 0x2000-byte
// ring dictionary, an 18-byte lookahead, and the binary match tree shared with
// Lzss_InsertString_00436000 and Lzss_RemoveNode_00436210.
namespace {

class LzssBitWriter_004359B0 {
public:
    explicit LzssBitWriter_004359B0(unsigned char* output)
        : output_(output), size_(0), current_byte_(0), bit_mask_(0x80) {
    }

    __forceinline void WriteBit(unsigned int bit) {
        if (bit != 0)
            current_byte_ |= bit_mask_;
        bit_mask_ >>= 1;
        if (bit_mask_ == 0) {
            output_[size_] = static_cast<unsigned char>(current_byte_);
            ++size_;
            current_byte_ = 0;
            bit_mask_ = 0x80;
        }
    }

    __forceinline void WriteBits(unsigned int value, unsigned int count) {
        while (count != 0) {
            --count;
            WriteBit((value >> count) & 1u);
        }
    }

    int Size() const {
        return size_;
    }

private:
    unsigned char* output_;
    int size_;
    unsigned int current_byte_;
    unsigned int bit_mask_;
};

} // namespace

extern "C" __declspec(noinline) unsigned char* __stdcall Lzss_Compress_004359B0(
    const unsigned char* input, int input_size, int* output_size) {
    const unsigned int allocation_size =
        static_cast<unsigned int>(input_size) * 2u;
    unsigned char* const output = static_cast<unsigned char*>(
        asm_malloc_00452706(allocation_size));
    if (output == 0)
        return 0;

    *output_size = 0;

    volatile unsigned char* const dictionary =
        reinterpret_cast<volatile unsigned char*>(data_0048f868);
    for (int i = 0; i < 0x2000; ++i)
        dictionary[i] = 0;

    volatile int* const tree_words =
        reinterpret_cast<volatile int*>(data_00477858);
    for (int node = 1; node <= 0x2000; ++node) {
        const int word = node * 3;
        tree_words[word + 0] = 0;
        tree_words[word + 1] = 0;
        tree_words[word + 2] = 0;
    }

    int input_position = 0;
    int lookahead = 0;
    while (input_position < input_size && lookahead < 0x12) {
        dictionary[lookahead + 1] = input[input_position];
        ++input_position;
        ++lookahead;
    }

    const int root = 0x2000;
    data_00477858[root].right = 1;
    data_00477858[1].parent = root;

    int ring_position = 1;
    int match_length = 0;
    int match_position = 0;
    LzssBitWriter_004359B0 bits(output);

    while (lookahead > 0) {
        int token_length = match_length;
        if (token_length > lookahead)
            token_length = lookahead;

        int consumed;
        if (token_length <= 2) {
            bits.WriteBit(1);
            bits.WriteBits(dictionary[ring_position], 8);
            consumed = 1;
        } else {
            bits.WriteBit(0);
            bits.WriteBits(static_cast<unsigned int>(match_position), 13);
            bits.WriteBits(static_cast<unsigned int>(token_length - 3), 4);
            consumed = token_length;
        }

        while (consumed != 0) {
            const int expired_position = (ring_position + 0x12) & 0x1fff;
            if (data_00477858[expired_position].parent != 0)
                Lzss_RemoveNode_00436210(expired_position);

            if (input_position < input_size) {
                dictionary[expired_position] = input[input_position];
                ++input_position;
            } else {
                --lookahead;
            }

            const int old_ring_position = ring_position;
            ring_position = (ring_position + 1) & 0x1fff;
            if (lookahead != 0) {
                match_length = Lzss_InsertString_00436000(
                    old_ring_position, ring_position, &match_position);
            }
            --consumed;
        }
    }

    // The terminator is a zero flag and a zero 13-bit position. Retail writes
    // only complete output bytes; a final partial byte remains implicit.
    bits.WriteBit(0);
    bits.WriteBits(0, 13);
    *output_size = bits.Size();
    return output;
}
