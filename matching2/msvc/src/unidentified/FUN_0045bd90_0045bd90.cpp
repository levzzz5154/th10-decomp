// 0x0045BD90..0x0045BE77: append a NUL-terminated string to another.
// Keep the original C-linkage name and x86 __cdecl boundary.
extern "C" __declspec(noinline) char* __cdecl asm_FUN_0045bd90_0045bd90(
    char* destination, const char* source) {
    char* append_at = destination;
    while (*append_at != '\0') {
        ++append_at;
    }

    while ((*append_at++ = *source++) != '\0') {
    }

    return destination;
}
