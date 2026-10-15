extern "C" int __fastcall asm_GetPrimaryLen_0045c527(int, const char* text) {
    int length = 0;
    for (;;) {
        char c = *text++;
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) break;
        ++length;
    }
    return length;
}
