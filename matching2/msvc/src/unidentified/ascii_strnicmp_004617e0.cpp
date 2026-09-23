// 0x004617E0..0x00461840: ___ascii_strnicmp
// Compare at most count bytes after folding ASCII uppercase letters only.
extern "C" int __cdecl asm_ascii_strnicmp_004617e0(
    const char* left, const char* right, unsigned int count) {
    while (count != 0) {
        const unsigned char left_byte =
            static_cast<unsigned char>(*left++);
        const unsigned char right_byte =
            static_cast<unsigned char>(*right++);

        const unsigned char left_folded =
            (left_byte >= 'A' && left_byte <= 'Z')
                ? static_cast<unsigned char>(left_byte + ('a' - 'A'))
                : left_byte;
        const unsigned char right_folded =
            (right_byte >= 'A' && right_byte <= 'Z')
                ? static_cast<unsigned char>(right_byte + ('a' - 'A'))
                : right_byte;

        if (left_folded != right_folded) {
            return left_folded < right_folded ? -1 : 1;
        }
        if (left_byte == 0) {
            return 0;
        }
        --count;
    }
    return 0;
}
