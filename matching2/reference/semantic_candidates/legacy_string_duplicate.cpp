// Semantic candidate for 0x00435220..0x0043524E (47 bytes).
// Retail receives text in EDI and has no stack arguments. This explicit
// stdcall parameter documents the input without claiming a private ABI match.
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

extern "C" char* __stdcall LegacyString_Duplicate_00435220(const char* text) {
    const char* end = text;
    while (*end++) {}
    char* copy = static_cast<char*>(asm_malloc_00452706(static_cast<unsigned int>(end - text)));
    if (copy) {
        char* destination = copy;
        // Copy through the current terminator after malloc returns. A cached
        // length would differ if the source changed during allocation.
        while ((*destination++ = *text++) != 0) {}
    }
    return copy;
}
