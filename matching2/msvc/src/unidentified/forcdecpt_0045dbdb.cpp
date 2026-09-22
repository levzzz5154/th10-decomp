extern "C" int __cdecl asm_tolower_00460cee(int);
extern "C" int __cdecl asm_isdigit_0045685e(int);
extern "C" char data_00473af4;

extern "C" void __cdecl asm_forcdecpt_0045dbdb(char* text) {
    if (asm_tolower_00460cee(*text) != 'e') {
        do { ++text; } while (asm_isdigit_0045685e(*text));
    }
    char previous = *text;
    *text++ = data_00473af4;
    char written;
    do {
        char next = *text;
        *text = previous;
        previous = next;
        written = *text++;
    } while (written);
}
