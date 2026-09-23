// 0x0045BED0..0x0045BF2F: fill a byte range and return its original address.
extern "C" void* __cdecl asm_memset_0045bed0(
    void* destination, int value, unsigned int size) {
    unsigned char* output = static_cast<unsigned char*>(destination);
    const unsigned char fill = static_cast<unsigned char>(value);

    for (unsigned int index = 0; index < size; ++index)
        output[index] = fill;

    return destination;
}
