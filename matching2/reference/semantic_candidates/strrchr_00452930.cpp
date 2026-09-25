extern "C" char* __cdecl asm_strrchr_00452930(
    const char* text, int character) {
    const unsigned char target = static_cast<unsigned char>(character);
    const char* last_match = 0;

    do {
        if (static_cast<unsigned char>(*text) == target)
            last_match = text;
    } while (*text++ != '\0');

    return const_cast<char*>(last_match);
}
