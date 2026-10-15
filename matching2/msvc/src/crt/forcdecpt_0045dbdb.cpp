extern "C" int __cdecl asm_tolower_00460cee(int);
extern "C" int __cdecl asm_isdigit_0045685e(int);
extern "C" char g_crt_decimal_point;

extern "C" void __cdecl asm_forcdecpt_0045dbdb(char* text) {
    if (asm_tolower_00460cee(*text) != 'e') {
        do { ++text; } while (asm_isdigit_0045685e(*text));
    }
    char previous = *text;
    *text++ = g_crt_decimal_point;
    char written;
    do {
        char next = *text;
        *text = previous;
        previous = next;
        written = *text++;
    } while (written);
}
