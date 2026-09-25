// Semantic implementation for the retail _strcmp entry at 0x0045BF30.
// The C-linkage name is retained for existing assembly callers.
extern "C" int __cdecl asm_strcmp_0045bf30(const char* left, const char* right) {
    for (;;) {
        const unsigned char left_byte = static_cast<unsigned char>(*left++);
        const unsigned char right_byte = static_cast<unsigned char>(*right++);

        if (left_byte != right_byte) {
            return left_byte < right_byte ? -1 : 1;
        }
        if (left_byte == 0) {
            return 0;
        }
    }
}
