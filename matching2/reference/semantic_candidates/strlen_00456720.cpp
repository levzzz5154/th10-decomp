#include <cstddef>
#include <cstdint>
#include <cstring>

// 0x00456720..0x004567AA: Visual Studio _strlen implementation.
// Aligns the input, scans four bytes at a time, then verifies candidate words.
extern "C" std::size_t __cdecl asm_strlen_00456720(const char* text) {
    const unsigned char* const start =
        reinterpret_cast<const unsigned char*>(text);
    const unsigned char* cursor = start;

    while ((reinterpret_cast<std::uintptr_t>(cursor) & 3u) != 0) {
        if (*cursor == '\0') {
            return static_cast<std::size_t>(cursor - start);
        }
        ++cursor;
    }

    for (;;) {
        std::uint32_t word;
        std::memcpy(&word, cursor, sizeof(word));
        cursor += sizeof(word);

        const std::uint32_t zero_byte_candidates =
            ((word + 0x7efefeffu) ^ ~word) & 0x81010100u;
        if (zero_byte_candidates == 0) {
            continue;
        }

        const unsigned char* const bytes = cursor - sizeof(word);
        if (bytes[0] == '\0') {
            return static_cast<std::size_t>(bytes - start);
        }
        if (bytes[1] == '\0') {
            return static_cast<std::size_t>(bytes - start + 1);
        }
        if (bytes[2] == '\0') {
            return static_cast<std::size_t>(bytes - start + 2);
        }
        if (bytes[3] == '\0') {
            return static_cast<std::size_t>(bytes - start + 3);
        }
    }
}
