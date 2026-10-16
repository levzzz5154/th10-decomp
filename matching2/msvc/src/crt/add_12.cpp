extern "C" int __cdecl asm_addl_00460798(
        unsigned int left, unsigned int right, unsigned int* sum_out);

// 0x004607B9..0x00460816: Add two three-word values with carry propagation.
extern "C" void __cdecl asm_add_12_004607b9(
        unsigned int* destination, const unsigned int* source) {
    if (asm_addl_00460798(destination[0], source[0], destination)) {
        if (asm_addl_00460798(destination[1], 1, destination + 1))
            ++destination[2];
    }
    if (asm_addl_00460798(destination[1], source[1], destination + 1))
        ++destination[2];
    asm_addl_00460798(destination[2], source[2], destination + 2);
}
