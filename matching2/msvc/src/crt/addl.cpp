// 0x00460798..0x004607B8: Add two words and report carry out.
extern "C" int __cdecl asm_addl_00460798(
        unsigned int left, unsigned int right, unsigned int* sum_out) {
    unsigned int sum = left + right;
    int carry = 0;
    if (sum < left || sum < right) carry = 1;
    *sum_out = sum;
    return carry;
}
