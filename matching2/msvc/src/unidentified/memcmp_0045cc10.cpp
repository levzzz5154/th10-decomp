// 0x0045CC10..0x0045CCC7: bounded byte comparison (_memcmp).
// The retail routine has aligned word and unaligned byte paths; both compare
// bytes in address order and expose only the sign of the first difference.
extern "C" int __cdecl asm_memcmp_0045cc10(
    const void* first, const void* second, unsigned int byte_count) {
    const unsigned char* const lhs =
        static_cast<const unsigned char*>(first);
    const unsigned char* const rhs =
        static_cast<const unsigned char*>(second);

    for (unsigned int index = 0; index < byte_count; ++index) {
        const unsigned char left = lhs[index];
        const unsigned char right = rhs[index];

        if (left != right) {
            return left < right ? -1 : 1;
        }
    }

    return 0;
}
