// Semantic candidates for DecryptDatBuffer (0x0044B0D0, 323 bytes) and
// EncryptDatBuffer (0x0044B220, 307 bytes). Not exact-build inputs.
// Retail receives key in AL and the other five arguments on the stack,
// with RET 20. These conventional six-argument entries expose that key
// explicitly; a real native-LTCG caller cluster must recover the private ABI.
#include <string.h>

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* memory);

namespace {

// Retail uses signed division and comparisons. Tiny final remainders are
// excluded, as is one byte for an odd total size. For example, size 1 with
// block size 16 yields -1 and skips transformation after snapshot allocation.
__forceinline int TransformLength(int size, int block_size) {
    int remainder = size % block_size;
    int short_tail = remainder < block_size / 4 ? remainder : 0;
    return size - ((size & 1) + short_tail);
}

__forceinline unsigned char* Snapshot(const unsigned char* data, int size, int limit) {
    int count = size < limit ? size : limit;
    unsigned char* copy = static_cast<unsigned char*>(
        asm_malloc_00452706(static_cast<unsigned int>(count)));
    if (copy)
        memcpy(copy, data, static_cast<unsigned int>(count));
    return copy;
}

} // namespace

extern "C" unsigned char* __stdcall Dat_Decrypt_0044b0d0(
        unsigned char* data, int size, unsigned char key, unsigned char step,
        int block_size, int byte_limit) {
    int remaining = TransformLength(size, block_size);
    unsigned char* snapshot = Snapshot(data, size, byte_limit);
    if (!snapshot)
        return data;

    const unsigned char* source = snapshot;
    unsigned char* block = data;
    while (remaining > 0 && byte_limit > 0) {
        if (remaining < block_size)
            block_size = remaining;

        // Fill alternating positions backwards, starting with the last byte.
        // The second pass fills the positions the first pass skipped.
        for (int position = block_size - 1; position >= 0; position -= 2) {
            block[position] = *source++ ^ key;
            key = static_cast<unsigned char>(key + step);
        }
        for (int position = block_size - 2; position >= 0; position -= 2) {
            block[position] = *source++ ^ key;
            key = static_cast<unsigned char>(key + step);
        }
        block += block_size;
        remaining -= block_size;
        // The limit decides whether to start another block. It does not clip
        // the current block, and may become negative after that block ends.
        byte_limit -= block_size;
    }
    asm_free_00452422(snapshot);
    return data;
}

extern "C" unsigned char* __stdcall Dat_Encrypt_0044b220(
        unsigned char* data, int size, unsigned char key, unsigned char step,
        int block_size, int byte_limit) {
    int remaining = TransformLength(size, block_size);
    unsigned char* snapshot = Snapshot(data, size, byte_limit);
    if (!snapshot)
        return data;

    const unsigned char* block = snapshot;
    unsigned char* destination = data;
    while (remaining > 0 && byte_limit > 0) {
        if (remaining < block_size)
            block_size = remaining;
        for (int position = block_size - 1; position >= 0; position -= 2) {
            *destination++ = block[position] ^ key;
            key = static_cast<unsigned char>(key + step);
        }
        for (int position = block_size - 2; position >= 0; position -= 2) {
            *destination++ = block[position] ^ key;
            key = static_cast<unsigned char>(key + step);
        }
        block += block_size;
        remaining -= block_size;
        byte_limit -= block_size;
    }
    asm_free_00452422(snapshot);
    return data;
}
