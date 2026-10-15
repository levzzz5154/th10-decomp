extern "C" unsigned char data_00473af4;
extern "C" void __cdecl asm_unassigned_0045dc17(char* text) {
    char* cursor = text;
    char decimal = static_cast<char>(data_00473af4);
    while (*cursor && *cursor != decimal) ++cursor;
    char current = *cursor++;
    if (!current) return;
    while (*cursor && *cursor != 'e' && *cursor != 'E') ++cursor;
    char* suffix = cursor;
    do { --cursor; } while (*cursor == '0');
    if (*cursor == decimal) --cursor;
    char ch;
    do {
        ch = *suffix;
        ++cursor;
        ++suffix;
        *cursor = ch;
    } while (ch);
}
