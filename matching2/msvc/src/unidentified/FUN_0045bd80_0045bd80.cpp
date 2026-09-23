// 0x0045BD80 is a callable C-string copy entry. Its short retail entry jumps
// into the copy loop shared with the adjacent strcat implementation.
extern "C" __declspec(noinline) char* __cdecl asm_FUN_0045bd80_0045bd80(
    char* destination, const char* source) {
    char* result = destination;
    while ((*destination++ = *source++) != '\0') {
    }
    return result;
}
