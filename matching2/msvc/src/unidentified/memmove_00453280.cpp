#include <cstddef>
#include <cstdint>

// 0x00453280..0x004535BC: semantic reconstruction of the VS 2003 CRT _memmove.
// The retail word-copy and dispatch-table code is represented by its byte-copy
// behavior; matching its optimized instruction sequence is not claimed.
extern "C" void* __cdecl asm_memmove_00453280(
    void* destination, const void* source, std::size_t size) {
    auto* destinationBytes = static_cast<unsigned char*>(destination);
    const auto* sourceBytes = static_cast<const unsigned char*>(source);

    const std::uintptr_t destinationAddress =
        reinterpret_cast<std::uintptr_t>(destination);
    const std::uintptr_t sourceAddress =
        reinterpret_cast<std::uintptr_t>(source);

    // Copy backwards only when the destination begins inside the source range.
    if (destinationAddress > sourceAddress &&
        destinationAddress - sourceAddress < size) {
        for (std::size_t remaining = size; remaining != 0; --remaining) {
            destinationBytes[remaining - 1] = sourceBytes[remaining - 1];
        }
    } else {
        for (std::size_t index = 0; index < size; ++index) {
            destinationBytes[index] = sourceBytes[index];
        }
    }

    return destination;
}
