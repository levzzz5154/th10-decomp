extern "C" int __cdecl crt_addl(
        unsigned int left, unsigned int right, unsigned int* sum_out);

// 0x0045D2FC..0x0045D348: Increment a mantissa bit and propagate carry.
extern "C" void __cdecl crt_IncMan(unsigned int* words, int bit) {
    int index = bit / 32;
    unsigned int* cursor = words + index;
    int carry = crt_addl(*cursor, 1u << (31 - bit % 32), cursor);
    --index;
    if (index >= 0) {
        cursor = words + index;
        do {
            if (!carry) return;
            carry = crt_addl(*cursor, 1, cursor);
            --index;
            --cursor;
        } while (index >= 0);
    }
}
