// 0x0045A75E..0x0045A77D: __store_str
// The retail helper places its arguments in EAX, ECX, and EDX.  The region
// symbol is retained here with an ordinary source-local C++ interface; all
// recovered callers now pass the cursor, capacity, and source explicitly.
extern "C" void __cdecl asm_store_str_0045a75e(
    char** output_cursor,
    unsigned int* remaining_capacity,
    const char* source) {
    while (*remaining_capacity != 0 && *source != '\0') {
        **output_cursor = *source;
        ++*output_cursor;
        ++source;
        --*remaining_capacity;
    }
}
