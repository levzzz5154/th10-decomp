// Compiler context only; never selected as recovered game code. Retail's
// callers pass both constant and per-file keys; calls of both kinds make the
// link-time compiler choose the same private convention (key in AL).
#include "../../src/archive/crypt.cpp"

struct DatCryptContextKey {
    unsigned char key;
    unsigned char step;
    unsigned char reserved[2];
    int block_size;
    int limit;
};

#pragma inline_depth(0)
#pragma code_seg(".text$crypt05_context")
extern "C" int __stdcall DatCryptCompilerContext(unsigned char** buffers, int* sizes,
                                                 const DatCryptContextKey* keys, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i) {
        const DatCryptContextKey* k = &keys[sizes[i] & 7];
        result += (int)Dat_Decrypt(buffers[i], sizes[i], k->key, k->step, k->block_size, k->limit);
        result += (int)Dat_Decrypt(buffers[i], 16, 0x1B, 0x37, 16, 16);
        result += (int)Dat_Encrypt(buffers[i], sizes[i], k->key, k->step, k->block_size, k->limit);
        result += (int)Dat_Encrypt(buffers[i], 16, 0x1B, 0x37, 16, 16);
    }
    return result;
}
#pragma code_seg()
#pragma inline_depth()
