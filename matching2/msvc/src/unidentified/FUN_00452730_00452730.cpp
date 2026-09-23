// 0x00452730: return the first byte equal to character in text.
// Express the byte-search semantics directly; the original aligned dword scan
// is not required for the result. A linker alias retains the retail C name for
// existing assembly call sites while this semantic name stays canonical.
#pragma comment(linker, "/alternatename:_asm_FUN_00452730_00452730=_FirstByteSearch_00452730")
extern "C" char* __cdecl FirstByteSearch_00452730(
        const char* text, int character) {
    const unsigned char target = static_cast<unsigned char>(character);
    const unsigned char* cursor =
        reinterpret_cast<const unsigned char*>(text);

    for (;;) {
        const unsigned char current = *cursor;
        if (current == target)
            return const_cast<char*>(reinterpret_cast<const char*>(cursor));
        if (current == 0)
            return 0;
        ++cursor;
    }
}
