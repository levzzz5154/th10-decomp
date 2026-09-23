extern "C" char* __cdecl asm_FUN_0045bd90_0045bd90(
    char* destination, const char* source);

extern "C" void __cdecl asm_strcats_00455990(void* destination, int count, ...) {
    int remaining = count;
    if (remaining > 0) {
        int* argument = &count;
        do {
            ++argument;
            asm_FUN_0045bd90_0045bd90(
                static_cast<char*>(destination),
                reinterpret_cast<const char*>(*argument));
            --remaining;
        } while (remaining != 0);
    }
}
