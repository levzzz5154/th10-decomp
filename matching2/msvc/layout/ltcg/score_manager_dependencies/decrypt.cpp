// 0x0044B0D0: undo the DAT interleaved-XOR cipher in place.
//
// The data is processed in blocks.  Each block was stored as two interleaved
// descending runs - last byte, last-but-two, ... then last-but-one,
// last-but-three, ... - with every byte XORed against a rolling key that
// advances by `step` per byte and carries over into the next block.  A copy
// of the (possibly limited) input is taken first so the block can be filled
// in place.
//
// A short final remainder (under a quarter block) and the last byte of an
// odd-sized buffer are left untouched.  `limit` only decides whether another
// block starts; it never clips the current one.  All comparisons are signed.
//
// Retail passes the key in AL and the rest on the stack (RET 20); native LTCG
// picks that from the callers, so the body is compiled in the cluster
// layout/ltcg/dat_crypt_0044b0d0.json.
#include <string.h>

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* memory);

#pragma code_seg(".text$05b")
__declspec(noinline) unsigned char* Dat_Decrypt(unsigned char* data, int size, unsigned char key,
                                                unsigned char step, int block_size, int limit) {
    int remainder = size % block_size;
    int tail = remainder < block_size / 4 ? remainder : 0;
    int count = limit > size ? size : limit;
    unsigned char* out = data;
    unsigned char* snapshot = (unsigned char*)asm_malloc_00452706(count);
    unsigned char* in = snapshot;
    if (!snapshot)
        return data;
    size -= (size & 1) + tail;
    memcpy(snapshot, data, count);
    while (size > 0 && limit > 0) {
        if (size < block_size)
            block_size = size;
        unsigned char* end = out + block_size;
        out = end;
        unsigned char* p = end - 1;
        for (int i = (block_size + 1) / 2; i > 0; i--) {
            *p = *in ^ key;
            p -= 2;
            key += step;
            in++;
        }
        p = end - 2;
        for (int i = block_size / 2; i > 0; i--) {
            *p = *in ^ key;
            p -= 2;
            key += step;
            in++;
        }
        size -= block_size;
        limit -= block_size;
    }
    asm_free_00452422(snapshot);
    return data;
}
#pragma code_seg()
