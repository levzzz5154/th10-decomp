// The replay save cluster's copy of the second cipher from
// src/archive/crypt.cpp. It is an ABI anchor: the whole-program pass gives
// the key argument its retail AL register, and the layout places the body at
// the retail address so the save routine's calls bake the retail
// displacement. Not recovered game code itself.
#include <string.h>
#include "th10/archive/crypt.hpp"

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* memory);

#pragma code_seg(".text$rsave03")
__declspec(noinline) unsigned char* Dat_Encrypt(unsigned char* data, int size, unsigned char key,
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
        unsigned char* end = in + block_size;
        int i;
        // The mirror image: plain bytes are taken from the back of the
        // block and the cipher bytes are written in order.
        in = end - 1;
        for (i = (block_size + 1) / 2; i > 0; i--) {
            *out = *in ^ key;
            in -= 2;
            key += step;
            out++;
        }
        in = end - 2;
        for (i = block_size / 2; i > 0; i--) {
            *out = *in ^ key;
            in -= 2;
            key += step;
            out++;
        }
        in = end;
        size -= block_size;
        limit -= block_size;
    }
    asm_free_00452422(snapshot);
    return data;
}
#pragma code_seg()
