#include "archive.hpp"
#ifndef ARCHIVE_DECRYPT_SECTION
#define ARCHIVE_DECRYPT_SECTION ".text$a04decrypt"
#endif
#pragma code_seg(ARCHIVE_DECRYPT_SECTION)
extern "C" __declspec(noinline) unsigned char* __stdcall DatDecrypt(unsigned char* data, int size, unsigned char key,
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
