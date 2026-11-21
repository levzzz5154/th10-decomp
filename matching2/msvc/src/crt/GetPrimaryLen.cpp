extern "C" int __fastcall crt_libc_getqloc_GetPrimaryLen(int, const char* text) {
    int length = 0;
    for (;;) {
        char c = *text++;
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) break;
        ++length;
    }
    return length;
}
