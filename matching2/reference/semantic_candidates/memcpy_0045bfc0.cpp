#include <cstddef>
#include <cstdint>

// 0x0045BFC0..0x0045C2FC: semantic reconstruction of the VS 2003 CRT _memcpy.
// The retail aligned word-copy and dispatch-table paths are represented by
// byte-copy loops; matching the optimized instruction sequence is not claimed.
extern "C" void* __cdecl asm_memcpy_0045bfc0(
    void* destination, const void* source, std::size_t size) {
    unsigned char* destinationBytes = static_cast<unsigned char*>(destination);
    const unsigned char* sourceBytes = static_cast<const unsigned char*>(source);

    const std::uintptr_t destinationAddress =
        reinterpret_cast<std::uintptr_t>(destination);
    const std::uintptr_t sourceAddress =
        reinterpret_cast<std::uintptr_t>(source);

    // Match the retail branch to its reverse-copy path for destructive overlap.
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
