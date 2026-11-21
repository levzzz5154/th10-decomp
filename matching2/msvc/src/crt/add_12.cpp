extern "C" int __cdecl crt_addl(
        unsigned int left, unsigned int right, unsigned int* sum_out);

// 0x004607B9..0x00460816: Add two three-word values with carry propagation.
extern "C" void __cdecl crt_add_12(
        unsigned int* destination, const unsigned int* source) {
    if (crt_addl(destination[0], source[0], destination)) {
        if (crt_addl(destination[1], 1, destination + 1))
            ++destination[2];
    }
    if (crt_addl(destination[1], source[1], destination + 1))
        ++destination[2];
    crt_addl(destination[2], source[2], destination + 2);
}
