// 0x004359B0..0x00436360: the LZSS codec.
//
// The functions were compiled as one unit with link-time code generation,
// which is what gives the tree helpers their register conventions and lets
// the compressor inline one level of Lzss_DeleteString. Each function sits in
// its own section only so the build can place it at its retail address.
#include <string.h>
#include "th10/archive/lzss.hpp"

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

// ---------------------------------------------------------------------------
// Compressor

// Appends one bit to the output; `rack` collects the bits of the current byte
// and `mask` is the next bit to fill.
#define LZSS_OUTPUT_BIT(bit)                                                   \
    if (bit)                                                                   \
        rack |= mask;                                                          \
    mask >>= 1;                                                                \
    if (mask == 0) {                                                           \
        *outCursor++ = (unsigned char)rack;                                    \
        rack = 0;                                                              \
        mask = 0x80;                                                           \
    }

// Appends the bits of `code` from `topBit` downwards.
#define LZSS_OUTPUT_BITS(code, topBit)                                         \
    bits = (topBit);                                                           \
    while (bits != 0) {                                                        \
        LZSS_OUTPUT_BIT((code) & bits)                                         \
        bits >>= 1;                                                            \
    }

// Next input byte, or -1 at the end of the input.
#define LZSS_GETC(c)                                                           \
    if (inCursor - in < inSize)                                                \
        c = *inCursor++;                                                       \
    else                                                                       \
        c = -1;

#pragma code_seg(".text$lzss01_compress")
unsigned char* __stdcall Lzss_Compress(const unsigned char* in, int inSize, int* outSize) {
    unsigned char mask = 0x80;
    unsigned int rack = 0;
    unsigned char* outCursor;
    const unsigned char* inCursor;
    int i;
    int c;
    int look_ahead_bytes;
    int current_position;
    int replace_count;
    int match_length;
    int match_position;
    unsigned int bits;
    unsigned char* out;

    out = (unsigned char*)asm_malloc_00452706(inSize * 2);
    if (out == 0)
        return 0;
    inCursor = in;
    *outSize = 0;
    outCursor = out;
    Lzss_InitEncoder();
    current_position = 1;
    for (i = 0; i < LZSS_LOOK_AHEAD_SIZE; i++) {
        LZSS_GETC(c)
        if (c == -1)
            break;
        g_LzssWindow[current_position + i] = (unsigned char)c;
    }
    look_ahead_bytes = i;
    Lzss_InitTree(current_position);
    match_length = 0;
    match_position = 0;
    while (look_ahead_bytes > 0) {
        if (match_length > look_ahead_bytes)
            match_length = look_ahead_bytes;
        if (match_length <= LZSS_BREAK_EVEN) {
            replace_count = 1;
            LZSS_OUTPUT_BIT(1)
            LZSS_OUTPUT_BITS(g_LzssWindow[current_position], 0x80)
        } else {
            LZSS_OUTPUT_BIT(0)
            LZSS_OUTPUT_BITS(match_position, 1 << (LZSS_INDEX_BIT_COUNT - 1))
            LZSS_OUTPUT_BITS(match_length - (LZSS_BREAK_EVEN + 1), 1 << (LZSS_LENGTH_BIT_COUNT - 1))
            replace_count = match_length;
        }
        // Slide the window over the bytes just encoded.
        for (i = 0; i < replace_count; i++) {
            Lzss_DeleteString(LZSS_MOD_WINDOW(current_position + LZSS_LOOK_AHEAD_SIZE));
            LZSS_GETC(c)
            if (c == -1)
                look_ahead_bytes--;
            else
                g_LzssWindow[LZSS_MOD_WINDOW(current_position + LZSS_LOOK_AHEAD_SIZE)] = (unsigned char)c;
            current_position = LZSS_MOD_WINDOW(current_position + 1);
            if (look_ahead_bytes)
                match_length = Lzss_AddString(current_position, &match_position);
        }
    }
    // The bits of the last, partial byte are never written; the decoder reads
    // zero bits past the end of its input, which is the terminator anyway.
    LZSS_OUTPUT_BIT(0)
    LZSS_OUTPUT_BITS(LZSS_END_OF_STREAM, 1 << (LZSS_INDEX_BIT_COUNT - 1))
    *outSize = outCursor - out;
    return out;
}

// ---------------------------------------------------------------------------
// Decompressor
//
// A set flag bit is followed by an eight-bit literal, a clear one by a window
// position and a match length. Reading past `inSize` yields zero bits without
// advancing. The window is not cleared between calls.

// Loads the next input byte once the previous one has been used up.
#define LZSS_REFILL()                                                          \
    if (inBitMask == 0x80) {                                                   \
        currByte = *inCursor;                                                  \
        if (inCursor - in >= inSize)                                           \
            currByte = 0;                                                      \
        else                                                                   \
            inCursor++;                                                        \
    }

#define LZSS_NEXT_BIT()                                                        \
    inBitMask >>= 1;                                                           \
    if (inBitMask == 0)                                                        \
        inBitMask = 0x80;

// Accumulates the bits from `topBit` downwards into `value`.
#define LZSS_INPUT_BITS(value, topBit)                                         \
    inBits = (topBit);                                                         \
    while (inBits != 0) {                                                      \
        LZSS_REFILL()                                                          \
        if (currByte & inBitMask)                                              \
            value |= inBits;                                                   \
        inBits >>= 1;                                                          \
        LZSS_NEXT_BIT()                                                        \
    }

#pragma code_seg(".text$lzss03_decompress")
extern "C" unsigned char* __stdcall DecompressDatLzss2(
    const unsigned char* in, int inSize, unsigned char* out, unsigned int outSize) {
    const unsigned char* inCursor;
    unsigned char* outCursor;
    unsigned char inBitMask = 0x80;
    unsigned int currByte = 0;
    unsigned int current_position;
    unsigned int inBits;
    unsigned int c;
    unsigned int match_position;
    int match_length;
    int i;
    unsigned int bits;

    if (out == 0) {
        out = (unsigned char*)asm_malloc_00452706(outSize);
        if (out == 0)
            return 0;
    }
    inCursor = in;
    outCursor = out;
    current_position = 1;
    for (;;) {
        LZSS_REFILL()
        unsigned int isLiteral = currByte & inBitMask;
        LZSS_NEXT_BIT()
        if (isLiteral != 0) {
            c = 0;
            LZSS_INPUT_BITS(c, 0x80)
            *outCursor++ = (unsigned char)c;
            g_LzssWindow[current_position] = (unsigned char)c;
            current_position = LZSS_MOD_WINDOW(current_position + 1);
        } else {
            bits = 0;
            LZSS_INPUT_BITS(bits, 1 << (LZSS_INDEX_BIT_COUNT - 1))
            match_position = bits;
            if (match_position == LZSS_END_OF_STREAM)
                break;
            bits = 0;
            LZSS_INPUT_BITS(bits, 1 << (LZSS_LENGTH_BIT_COUNT - 1))
            match_length = bits + LZSS_BREAK_EVEN;
            for (i = 0; i <= match_length; i++) {
                c = g_LzssWindow[LZSS_MOD_WINDOW(match_position + i)];
                *outCursor++ = (unsigned char)c;
                g_LzssWindow[current_position] = (unsigned char)c;
                current_position = LZSS_MOD_WINDOW(current_position + 1);
            }
        }
    }
    // Skip the unused bits of the final byte.
    while (inBitMask != 0x80) {
        inBitMask >>= 1;
        if (inBitMask == 0)
            break;
    }
    return out;
}

// ---------------------------------------------------------------------------
// Match tree

// Makes window position `r` the tree's only string.
#pragma code_seg(".text$lzss05_inittree")
void Lzss_InitTree(int r) {
    g_LzssTree[LZSS_TREE_ROOT].larger_child = r;
    g_LzssTree[r].parent = LZSS_TREE_ROOT;
    g_LzssTree[r].larger_child = LZSS_UNUSED;
    g_LzssTree[r].smaller_child = LZSS_UNUSED;
}

// Clears the window and detaches every tree node.
#pragma code_seg(".text$lzss07_initencoder")
void Lzss_InitEncoder() {
    int i;

    memset(g_LzssWindow, 0, sizeof(g_LzssWindow));
    for (i = 0; i < LZSS_WINDOW_SIZE + 1; i++) {
        g_LzssTree[i].parent = LZSS_UNUSED;
        g_LzssTree[i].smaller_child = LZSS_UNUSED;
        g_LzssTree[i].larger_child = LZSS_UNUSED;
    }
}

// Inserts the string at window position `new_node` and returns the length of
// the longest match met on the way down, with its position in
// *match_position. A full-length duplicate is replaced by the new string so
// the tree never holds two equal strings.
#pragma code_seg(".text$lzss09_addstring")
int Lzss_AddString(int new_node, int* match_position) {
    int i;
    int test_node;
    int delta;
    int match_length;
    int* child;

    if (new_node == LZSS_END_OF_STREAM)
        return 0;
    test_node = g_LzssTree[LZSS_TREE_ROOT].larger_child;
    match_length = 0;
    for (;;) {
        for (i = 0; i < LZSS_LOOK_AHEAD_SIZE; i++) {
            delta = g_LzssWindow[LZSS_MOD_WINDOW(new_node + i)] -
                    g_LzssWindow[LZSS_MOD_WINDOW(test_node + i)];
            if (delta != 0)
                break;
        }
        if (i >= match_length) {
            match_length = i;
            *match_position = test_node;
            if (match_length >= LZSS_LOOK_AHEAD_SIZE) {
                Lzss_ReplaceNode(test_node, new_node);
                return match_length;
            }
        }
        if (delta >= 0)
            child = &g_LzssTree[test_node].larger_child;
        else
            child = &g_LzssTree[test_node].smaller_child;
        if (*child == LZSS_UNUSED) {
            *child = new_node;
            g_LzssTree[new_node].parent = test_node;
            g_LzssTree[new_node].larger_child = LZSS_UNUSED;
            g_LzssTree[new_node].smaller_child = LZSS_UNUSED;
            return match_length;
        }
        test_node = *child;
    }
}

// Removes the string at window position `p` from the tree.
#pragma code_seg(".text$lzss11_deletestring")
void __fastcall Lzss_DeleteString(int p) {
    int replacement;

    if (g_LzssTree[p].parent == LZSS_UNUSED)
        return;
    if (g_LzssTree[p].larger_child == LZSS_UNUSED)
        Lzss_ContractNode(p, g_LzssTree[p].smaller_child);
    else if (g_LzssTree[p].smaller_child == LZSS_UNUSED)
        Lzss_ContractNode(p, g_LzssTree[p].larger_child);
    else {
        replacement = Lzss_FindNextNode(p);
        Lzss_DeleteString(replacement);
        Lzss_ReplaceNode(p, replacement);
    }
}

// Links `new_node`, the only child of `old_node`, to old_node's parent.
#pragma code_seg(".text$lzss12_contractnode")
void Lzss_ContractNode(int old_node, int new_node) {
    g_LzssTree[new_node].parent = g_LzssTree[old_node].parent;
    if (g_LzssTree[g_LzssTree[old_node].parent].larger_child == old_node)
        g_LzssTree[g_LzssTree[old_node].parent].larger_child = new_node;
    else
        g_LzssTree[g_LzssTree[old_node].parent].smaller_child = new_node;
    g_LzssTree[old_node].parent = LZSS_UNUSED;
}

// Puts `new_node`, which is not in the tree, in the place of `old_node`.
#pragma code_seg(".text$lzss14_replacenode")
void Lzss_ReplaceNode(int old_node, int new_node) {
    int parent;

    parent = g_LzssTree[old_node].parent;
    if (g_LzssTree[parent].smaller_child == old_node)
        g_LzssTree[parent].smaller_child = new_node;
    else
        g_LzssTree[parent].larger_child = new_node;
    g_LzssTree[new_node] = g_LzssTree[old_node];
    g_LzssTree[g_LzssTree[new_node].smaller_child].parent = new_node;
    g_LzssTree[g_LzssTree[new_node].larger_child].parent = new_node;
    g_LzssTree[old_node].parent = LZSS_UNUSED;
}

// The largest string smaller than `node`'s: the rightmost node of its smaller
// subtree.
#pragma code_seg(".text$lzss16_findnextnode")
int Lzss_FindNextNode(int node) {
    int next;

    next = g_LzssTree[node].smaller_child;
    while (g_LzssTree[next].larger_child != LZSS_UNUSED)
        next = g_LzssTree[next].larger_child;
    return next;
}
#pragma code_seg()
