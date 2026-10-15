// 0x0044B0D0..0x0044B352: the dat/score/replay byte cipher.
//
// Compiled with link-time code generation, which passes the key in AL. Each
// function sits in its own section only so the build can place it at its
// retail address.
#include <string.h>
#include "th10/archive/crypt.hpp"

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* memory);

#pragma code_seg(".text$crypt01_decrypt")
unsigned char* Dat_Decrypt(unsigned char* data, int size, unsigned char key,
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
        int i;
        // Cipher bytes arrive in order; the plain bytes are filled in from
        // the back of the block, every other one per pass.
        out = end - 1;
        for (i = (block_size + 1) / 2; i > 0; i--) {
            *out = *in ^ key;
            out -= 2;
            key += step;
            in++;
        }
        out = end - 2;
        for (i = block_size / 2; i > 0; i--) {
            *out = *in ^ key;
            out -= 2;
            key += step;
            in++;
        }
        out = end;
        size -= block_size;
        limit -= block_size;
    }
    asm_free_00452422(snapshot);
    return data;
}

#pragma code_seg(".text$crypt03_encrypt")
unsigned char* Dat_Encrypt(unsigned char* data, int size, unsigned char key,
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
