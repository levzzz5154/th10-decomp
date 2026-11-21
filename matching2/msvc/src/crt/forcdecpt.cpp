extern "C" int __cdecl crt_tolower(int);
extern "C" int __cdecl crt_isdigit(int);
extern "C" char g_crt_decimal_point;

extern "C" void __cdecl crt_forcdecpt(char* text) {
    if (crt_tolower(*text) != 'e') {
        do { ++text; } while (crt_isdigit(*text));
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
