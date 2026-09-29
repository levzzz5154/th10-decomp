// Semantic candidate for 0x004359B0..0x00435DB4. Not an exact-build input.
// The compressor shares an 8 KiB ring and a binary match tree with the
// maintained insertion/deletion helpers. See recovery_notes/lzss_compressor_004359b0.md.
#include <string.h>
#include "th10/game/compression_tree.hpp"

extern "C" unsigned char data_0048f868[0x2000];
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" int __fastcall Lzss_InsertString_00436000(int previous_position,
                                                  int position, int* best_position);

namespace {

class LzssInput {
public:
    LzssInput(const unsigned char* data, int size)
        : begin_(data), cursor_(data), size_(size) {}

    __forceinline int ReadByte() {
        if (cursor_ - begin_ >= size_)
            return -1;
        return *cursor_++;
    }

private:
    const unsigned char* begin_;
    const unsigned char* cursor_;
    int size_;
};

class LzssBitWriter {
public:
    LzssBitWriter() : cursor_(0), current_byte_(0), bit_mask_(0x80) {}
    void SetOutput(unsigned char* output) { cursor_ = output; }

    __forceinline void WriteBit(unsigned int bit) {
        if (bit)
            current_byte_ |= bit_mask_;
        bit_mask_ >>= 1;
        if (!bit_mask_) {
            *cursor_++ = static_cast<unsigned char>(current_byte_);
            current_byte_ = 0;
            bit_mask_ = 0x80;
        }
    }

    // The argument is the highest bit to emit, not a bit count.
    __forceinline void WriteBits(unsigned int value, unsigned int mask) {
        do {
            WriteBit(value & mask);
            mask >>= 1;
        } while (mask);
    }

    unsigned char* Cursor() const { return cursor_; }

private:
    unsigned char* cursor_;
    unsigned int current_byte_;
    unsigned char bit_mask_;
};

// Retail inlines one deletion level into the compressor. Only predecessor
// removal recurses through the separately recovered ECX-entry helper.
__forceinline void RemoveExpiredNode(int node) {
    CompressionTreeNode* old_node = &g_compression_tree.nodes[node];
    if (!old_node->parent)
        return;

    if (!old_node->right) {
        int replacement = old_node->left;
        g_compression_tree.nodes[replacement].parent = old_node->parent;
        int parent = old_node->parent;
        if (g_compression_tree.nodes[parent].right == node)
            g_compression_tree.nodes[parent].right = replacement;
        else
            g_compression_tree.nodes[parent].left = replacement;
    } else if (!old_node->left) {
        int replacement = old_node->right;
        g_compression_tree.nodes[replacement].parent = old_node->parent;
        int parent = old_node->parent;
        if (g_compression_tree.nodes[parent].right == node)
            g_compression_tree.nodes[parent].right = replacement;
        else
            g_compression_tree.nodes[parent].left = replacement;
    } else {
        int predecessor = old_node->left;
        while (g_compression_tree.nodes[predecessor].right)
            predecessor = g_compression_tree.nodes[predecessor].right;
        Lzss_RemoveNode_00436210(predecessor);
        int parent = old_node->parent;
        if (g_compression_tree.nodes[parent].left == node)
            g_compression_tree.nodes[parent].left = predecessor;
        else
            g_compression_tree.nodes[parent].right = predecessor;
        g_compression_tree.nodes[predecessor] = *old_node;
        g_compression_tree.nodes[g_compression_tree.nodes[predecessor].left].parent = predecessor;
        g_compression_tree.nodes[g_compression_tree.nodes[predecessor].right].parent = predecessor;
    }
    old_node->parent = 0;
}

} // namespace

extern "C" unsigned char* __stdcall Lzss_Compress_004359B0(
        const unsigned char* input, int input_size, int* output_size) {
    LzssBitWriter bits;
    unsigned char* output = static_cast<unsigned char*>(
        asm_malloc_00452706(static_cast<unsigned int>(input_size) * 2u));
    if (!output)
        return 0;

    LzssInput source(input, input_size);
    *output_size = 0;
    bits.SetOutput(output);
    memset(data_0048f868, 0, sizeof(data_0048f868));
    for (int node = 0; node <= 0x2000; ++node) {
        g_compression_tree.nodes[node].parent = 0;
        g_compression_tree.nodes[node].left = 0;
        g_compression_tree.nodes[node].right = 0;
    }

    int ring_position = 1;
    int lookahead = 0;
    for (; lookahead < 18; ++lookahead) {
        int value = source.ReadByte();
        if (value == -1)
            break;
        data_0048f868[ring_position + lookahead] = static_cast<unsigned char>(value);
    }

    g_compression_tree.nodes[0x2000].right = ring_position;
    g_compression_tree.nodes[ring_position].parent = 0x2000;
    g_compression_tree.nodes[ring_position].right = 0;
    g_compression_tree.nodes[ring_position].left = 0;

    int match_length = 0;
    int match_position = 0;
    while (lookahead > 0) {
        if (match_length > lookahead)
            match_length = lookahead;
        int consumed;
        if (match_length <= 2) {
            bits.WriteBit(1);
            bits.WriteBits(data_0048f868[ring_position], 0x80);
            consumed = 1;
        } else {
            bits.WriteBit(0);
            bits.WriteBits(match_position, 0x1000);
            bits.WriteBits(match_length - 3, 8);
            consumed = match_length;
        }

        for (int i = 0; i < consumed; ++i) {
            int expired_position = (ring_position + 18) & 0x1fff;
            RemoveExpiredNode(expired_position);
            int value = source.ReadByte();
            if (value == -1)
                --lookahead;
            else
                data_0048f868[expired_position] = static_cast<unsigned char>(value);
            int previous_position = ring_position;
            ring_position = (ring_position + 1) & 0x1fff;
            if (lookahead)
                match_length = Lzss_InsertString_00436000(
                    previous_position, ring_position, &match_position);
        }
    }

    // Only complete bytes are emitted. The zero flag and zero 13-bit position
    // terminate the stream; the decoder supplies zero bits after input ends.
    bits.WriteBit(0);
    bits.WriteBits(0, 0x1000);
    *output_size = static_cast<int>(bits.Cursor() - output);
    return output;
}
