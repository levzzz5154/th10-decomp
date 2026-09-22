extern "C" int data_00499314;
extern "C" unsigned char* data_00499348;
extern "C" unsigned char data_0046d275;
extern "C" void __cdecl asm_initmbctable_0045d2ac();
extern "C" int __cdecl asm_ismbblead_0045f590(unsigned int);

extern "C" unsigned char* __cdecl asm_wincmdln_004590d8() {
    int quoted = 0;
    if (data_00499314 == 0) asm_initmbctable_0045d2ac();
    unsigned char* text = data_00499348;
    if (!text) text = &data_0046d275;
    for (;;) {
        unsigned char ch = *text;
        if (ch <= ' ') {
            if (ch == 0) return text;
            if (!quoted) {
                while (*text && *text <= ' ') ++text;
                return text;
            }
        }
        if (ch == '"') quoted = !quoted;
        if (asm_ismbblead_0045f590(ch)) ++text;
        ++text;
    }
}
