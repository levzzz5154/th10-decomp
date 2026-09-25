// 0x0045D3BB: copy three 32-bit words from source to destination in order.
// Keep the copy forward rather than using memmove: overlap behavior follows
// the same per-word read-then-write order as the retail loop.
extern "C" void __cdecl asm_CopyMan_0045d3bb(
        unsigned int* destination, const unsigned int* source) {
    for (unsigned int wordIndex = 0; wordIndex < 3; ++wordIndex)
        destination[wordIndex] = source[wordIndex];
}
