#include <cstdint>

// 0x0045C4F2..0x0045C526: _LcidFromHexString.
// The first fastcall register slot is ignored; the input string arrives in EDX.
extern "C" int __fastcall asm_LcidFromHexString_0045c4f2(
    int ignored_ecx, const char* text) {
    (void)ignored_ecx;

    std::uint32_t result = 0;
    while (*text != '\0') {
        const unsigned char byte = static_cast<unsigned char>(*text++);
        int value = byte < 0x80u ? static_cast<int>(byte)
                                 : static_cast<int>(byte) - 0x100;

        // The retail routine maps only ASCII A-F/a-f. Other non-NUL bytes
        // remain signed character values and still participate in the fold.
        if (value >= 'a' && value <= 'f') {
            value -= 0x27;
        } else if (value >= 'A' && value <= 'F') {
            value -= 0x07;
        }

        // This is the retail 32-bit recurrence, including its wraparound:
        // (result - 3) * 16 + the sign-extended, possibly adjusted byte.
        result = ((result - 3u) << 4) + static_cast<std::uint32_t>(value);
    }

    return static_cast<int>(result);
}
