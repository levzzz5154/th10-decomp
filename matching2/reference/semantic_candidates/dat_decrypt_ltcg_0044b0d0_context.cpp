// Compiler context only; never selected as recovered game code.
#include "../../src/archive/dat_decrypt_0044b0d0.cpp"

struct DatCipher_0044b0d0 {
    unsigned char key;
    unsigned char step;
    unsigned char reserved[2];
    int block_size;
    int limit;
};

void __stdcall DatCryptSink_0044b220(unsigned char* data);

#pragma code_seg(".text$02context")
int __stdcall DatCryptContext_0044b0d0(unsigned char** buffers, int* sizes,
                                       const DatCipher_0044b0d0* ciphers, int count) {
    for (int i = 0; i < count; ++i) {
        const DatCipher_0044b0d0* cipher = &ciphers[sizes[i] & 7];
        DatCryptSink_0044b220(Dat_Decrypt(buffers[i], sizes[i], cipher->key, cipher->step,
                                          cipher->block_size, cipher->limit));
        DatCryptSink_0044b220(Dat_Decrypt(buffers[i], 16, 0x1B, 0x37, 16, 16));
    }
    return count;
}
#pragma code_seg()
